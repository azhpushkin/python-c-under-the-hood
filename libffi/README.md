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
  fibonacci(5) = 5
  fibonacci(6) = 8
  fibonacci(7) = 13
  fibonacci(8) = 21
  fibonacci(9) = 34
```

Compile and run libffi-demo:
```
$ cp ../basics/libdullmath.so ./
$ gcc libffi-demo.c -ldl -lffi -o libffi-demo.out
$ ./libffi-demo.out
  fib(5) is 5
  fib(6) is 8
  fib(7) is 13
  fib(8) is 21
  fib(9) is 34
```

