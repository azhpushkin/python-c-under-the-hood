## Compile `mymath` extension
Compile `mymath` with `gcc` and `python-config`:
**Note**: there is no need for `lib` prefix for mymath.so, because
python extensions do not need it.

```
$ gcc mymath.c -c $(python-config --cflags --includes --libs) -fPIC
$ gcc -shared mymath.o $(python-config --ldflags) -o mymath.so
```

Feel free to play with compiler library afterwards:
```python
>>> import mymath
>>> dir(mymath)
['__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__', 'square']
>>> mymath.square(2)
4
>>> mymath.square("two please")
TypeError: an integer is required (got typе str)
...
```


Here is examination of symbols inside of compiled library.
`mymath.so` does not implement Python C API functions:
```bash
$ python-config --ldflags
  -L/usr/lib  -lcrypt -lpthread -ldl  -lutil -lm -lm 
$ readelf -D --symbols mymath.so | grep PyArg_ParseTuple
  6: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND PyArg_ParseTuple
$ readelf -D --symbols mymath.so | grep PyLong_FromLong      
  3: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND PyLong_FromLong
```

But there is python library, that is shipped and linked to interpreter.
That library has all the machine code that extensions need:
```bash
$ ldd /usr/bin/python | grep libpython
  libpython3.8.so.1.0 => /usr/lib/libpython3.8.so.1.0 (0x00007fd3a5601000)
$ readelf /usr/lib/libpython3.8.so.1.0  --symbols  | grep PyArg_ParseTuple$
  1648: 0000000000128ef0   212 FUNC    GLOBAL DEFAULT    9 PyArg_ParseTuple
$ readelf /usr/lib/libpython3.8.so.1.0  --symbols  | grep PyLong_FromLong$ 
  1455: 0000000000112a50   648 FUNC    GLOBAL DEFAULT    9 PyLong_FromLong
```

## Running Cython and pybind11
There are also examples of Cython and pybind modules at `cython_demo.pyx`
and `pybind11_demo.cpp`. Make sure to install Cython and pybind11 before using them
(using OS-default package manager like `apt-get` does the trick).


Compile Cython extension:
```bash
$ cython cython_demo.pyx  # this creates cython_demo.c
$ gcc -shared cython_demo.c \
  $(python-config --cflags --includes --libs --ldflags) \
  -fPIC -o cython_demo.so
$ python
>>> import cython_demo
>>> cython_demo.fibonacci(10)
10
```

Compile pybind11 extension:
```bash
$ g++ -shared -std=c++11 pybind11_demo.cpp \
  $(python -m pybind11 --includes) \
  -fPIC -o pybind11_demo.so
$ python
>>> import pybind11_demo
>>> pybind11_demo.get_pi()
3.140000104904175
```