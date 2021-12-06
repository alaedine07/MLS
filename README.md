# Synopsis:
My simple implementation of the Linux `ls` command. Part of a School project

## Files:
`error.c`: handle displayed errors

`memory.c`: handle freeing memory operations

`hls.h`: header file contains function definitions

`hls.c`: Contains main functions

`files.c`: contains functions to operate on argument files

## Allowed functions and system calls:
```opendir (man 3 opendir)
readdir (man 3 readdir)
closedir (man 3 closedir)
exit (man 3 exit)
free (man 3 free)
lstat (man 2 lstat)
malloc (man 3 malloc)
perror (man 3 perror)
write (man 2 write)
printf (man 3 printf)
readlink (man 2 readlink)
ctime (man 3 ctime)
getpwuid (man 3 getpwuid)
getgrgid (man 3 getgrgid)
```

# Example output:

```
./mls -l
-rw-rw-r-- 1 alaedine alaedine	13	  Dec  6 16:50 README.md
-rwxrwxr-x 1 alaedine alaedine	102	  Dec  6 16:50 valtest.sh
-rw-rw-r-- 1 alaedine alaedine	741	  Dec  6 16:50 string.c
-rw-rw-r-- 1 alaedine alaedine  3846  Dec  6 16:50 files.c
-rwxrwxr-x 1 alaedine alaedine	36600 Dec  6 17:06 mls
-rw-rw-r-- 1 alaedine alaedine	3907  Dec  6 16:50 hls.c
-rwxrwxr-x 1 alaedine alaedine	50	  Dec  6 16:50 compile.sh
-rw-rw-r-- 1 alaedine alaedine	512	  Dec  6 16:50 memory.c
-rw-rw-r-- 1 alaedine alaedine	1421  Dec  6 16:50 hls.h
```
# Current BUGS:
- readir() missing one directory
- options `-l` returning error when used on a directory
# Next Features:
- Add more options
- Handle SUID and SGID bits
- Add sorting