apres analyse du programme on peut voir que le programme est compose d'une condition qui est la suivante :

```c
    if (*((int *)&v1) != 5276)
    {
        puts("\nInvalid Password!");
        return 1;
    }
```

on en deduit donc que la reponse est 5276
on essaye :

```
level00@OverRide:~$ ./level00 
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```