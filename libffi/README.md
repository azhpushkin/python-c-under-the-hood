First of all, make sure `libffi` is installed

```
$ ls /usr/lib/ | grep libffi
libffi.so
libffi.so.7
libffi.so.7.1.0
```

If not, using `apt-get` or any other package manager should do the trick.

> **Note**: following code lacks error messages, so if you run a program
> and it does not output anything, then probably something is not working fine
> (return code is not `0`).


Compile and run linking-demo:
```
$ cp ../basics/libdullmath.so ./
$ gcc linking-demo.c -ldl -o linking-demo.out
$ ./linking-demo.out
```

Compile and run libffi-demo:
```
$ cp ../basics/libdullmath.so ./
$ gcc libffi-demo.c -ldl -lffi -o libffi-demo.out
$ ./libffi-demo.out
```

