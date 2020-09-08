Compile the library:

```bash
$ gcc -shared -fPIC dullmath.c -o libdullmath.so
```

Run `readelf` to verify that functions are compiled:
```bash
$ readelf -D --symbols libdullmath.so | grep FUNC | grep GLOBAL
  5   1: 0000000000001109    74 FUNC    GLOBAL DEFAULT  11 fibonacci
  6   1: 0000000000001153    14 FUNC    GLOBAL DEFAULT  11 get_pi
```

In order to use the library, you need to make sure compiler will find it.
There are two ways to achieve this:

### 1. Move resulting file to system-wide default directory:
```bash
$ sudo cp libdullmath.so /usr/lib/
```
This one is easier, but you need sudo permissions for it.

In this way, you don't to do anything to make library work:
```bash
$ gcc -c main.c -o main.o
$ gcc main.o -ldullmath -o main.out
$ ./main.out
  10th fibonacci number is 55
```

### 2. Set compiler and environment flags

If you don't have sudo permissions or don't want to clutter up
system-wide directories, you can use compiler flags and `LD_LIBRARY_PATH` 
environment variable to define path to the library.


```bash
$ gcc -c main.c -o main.o
$
$ # set -L flag to current path (.)
$ # compiler will add given directory to lookup list
$ gcc main.o -L. -ldullmath -o main.out
$
$ # LD_LIBRARY_PATH is required for OS to find library at runtime
$ # as compilation does not fix location of the library
$ export LD_LIBRARY_PATH=$(pwd)  
$ ./main.out
  10th fibonacci number is 55
$ 
$ # Or also:
$ LD_LIBRARY_PATH=$(pwd) ./main.out
  10th fibonacci number is 55
```




