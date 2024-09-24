Here we just reverse engineer the `auth` to get the serial.
We enter a string like : `"123456"`. This give output the serial.

```Shell
./a.out 123456
Serial : 6231517
```

```Shell
level06@OverRide:~$ ./level06
***********************************
*               level06           *
***********************************
-> Enter Login: 123456
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6231517
Authenticated!
$
```

OR :
pour chercher le resultat du hash nous allons fouiller la memoire en execution avec GDB, premierement on voit un ptrace ce qui veut dire que nous allons commencer par contourner la securite une fois cela fait on va aller chercher le pointeur de la condition dans auth qui se definit comme de dernier 'cmp' de auth

```
(gdb) disas auth
...
   0x08048861 <+281>:   jl     0x804880f <auth+199>
   0x08048863 <+283>:   mov    0xc(%ebp),%eax
   0x08048866 <+286>:   cmp    -0x10(%ebp),%eax   <------ here -0x10(%ebp) est la valeur qu'on cherche
   0x08048869 <+289>:   je     0x8048872 <auth+298>
   0x0804886b <+291>:   mov    $0x1,%eax
   0x08048870 <+296>:   jmp    0x8048877 <auth+303>
   0x08048872 <+298>:   mov    $0x0,%eax
   0x08048877 <+303>:   leave
   0x08048878 <+304>:   ret
```

donc on determine les actions a faire ce qui nous donne cette suite logique :

```
(gdb) b ptrace
Breakpoint 1 at 0x80485f0
(gdb) b *0x08048866
Breakpoint 2 at 0x8048866
(gdb) r
Starting program: /home/users/level06/level06
***********************************
*               level06           *
***********************************
-> Enter Login: 118712
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: oui

Breakpoint 1, 0xf7f14990 in ptrace () from /lib32/libc.so.6
(gdb) step
Single stepping until exit from function ptrace,
which has no line number information.
0x080487ba in auth ()
(gdb) p $eax
$1 = -1
(gdb) set $eax=0
(gdb) c
Continuing.

Breakpoint 2, 0x08048866 in auth ()
(gdb) x $ebp-0x10
0xffffd628:     0x005f15e1
(gdb) p/d 0x005f15e1
$2 = 6231521
```

essayons :

```
level06@OverRide:~$ ./level06
***********************************
*               level06           *
***********************************
-> Enter Login: 118712
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6231521
Authenticated!
$ whoami
level07
```
