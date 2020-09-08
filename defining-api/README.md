Compile libexpo and copy dullmath:
```
$ gcc -shared -fPIC expo.c -o libexpo.so
$ cp ../basics/libdullmath.so ./
$ ls *.so
  libdullmath.so  libexpo.so
```


Then, you can run `main.c` to see how swapping libraries works:
```
$ gcc main.c -o main.out -ldl
$
$ ./main.out
Enter library name and function: ./libdullmath.so fibonacci
fibonacci(x), x:0-9
>>>  0 1 1 2 3 5 8 13 21 34 
$ 
$ ./main.out
Enter library name and function: ./libexpo.so square
square(x), x:0-9
>>>  0 1 4 9 16 25 36 49 64 81
$ 
$ ./main.out
Enter library name and function: ./libexpo.so pow3
pow3(x), x:0-9
>>>  0 1 8 27 64 125 216 343 512 729
```


There are also `api.h` and `api-usage-example.c`, but there is no
test stand to run those. Well, you still can examine source code! :D



