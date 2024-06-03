Upon analyzing the code, we can see two functions: test and decrypt. The test function compares a given number against 322424845. If the number is greater, the decrypt function is executed with a random number. Otherwise, decrypt is executed with the difference between the given number and 322424845.

The decrypt function performs an XOR operation on each character of the string "Q}|usfg~sf{}|a3" using the provided key. If this operation transforms "Q}|usfg~sf{}|a3" into "Congratulations", the script executes /bin/sh.

With this understanding, we can write a program that tests the decrypt function with keys ranging from 1 to 21 to determine which key successfully transforms the string.

```
gcc revert_decrypt.c -o revert
❯ ./revert
key : 0 
string : Q}|u`sfg~sf{}|a3

key : 1 
string : P|}targfrgz|}`2

key : 2 
string : S~wbqde|qdy~c1

key : 3 
string : R~vcped}pex~b0

key : 4 
string : Uyxqdwbczwbyxe7

key : 5 
string : Txypevcb{vc~xyd6

key : 6 
string : W{zsfu`axu`}{zg5

key : 7 
string : Vz{rgta`yta|z{f4

key : 8 
string : Yut}h{nov{nsuti;

key : 9 
string : Xtu|izonwzortuh:

key : 10 
string : [wvjylmtylqwvk9


key : 11 
string : Zvw~kxmluxmpvwj8


key : 12 
string : ]qpyljkrjwqpm?


key : 13 
string : \pqxm~kjs~kvpql>

key : 14 
string : _sr{n}hip}husro=

key : 15 
string : ^rszo|ihq|itrsn<

key : 16 
string : Amlepcvwncvkmlq#

key : 17 
string : @lmdqbwvobwjlmp"

key : 18 
string : Congratulations!
```

322424845 - 18 = 322424827

let's test this :

```
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```