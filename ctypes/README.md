Don't forget to copy the shared library from `basics` directory:

```
cp ../basics/libdullmath.so ./
```

Copy following commands to python interpreter to check out how ctypes works:
```python
>>> import ctypes
>>>
>>> lib = ctypes.CDLL(f'./libdullmath.so')
>>> lib.get_pi
<_FuncPtr object at 0x7f3671537b80>
>>> lib.fibonacci
<_FuncPtr object at 0x7f3671537700>
>>>
>>> lib.other_function   # wrong names are not found
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "/usr/lib/python3.8/ctypes/__init__.py", line 386, in __getattr__
    func = self.__getitem__(name)
  File "/usr/lib/python3.8/ctypes/__init__.py", line 391, in __getitem__
    func = self._FuncPtr((name_or_ordinal, self))
AttributeError: /home/.../libsimple.so: undefined symbol: other_function

>>> [lib.fibonacci(i) for i in range(7)]
[0, 1, 1, 2, 3, 5, 8]
>>> lib.get_pi()
0

>>> lib.get_pi.restype = ctypes.c_float
>>> lib.get_pi()
3.140000104904175
```

You may as well just run 
```
$ python try-ctypes.py
```
to see it in action with some additional fancy output.

### Using ctypes with C++

Compile `basics/dullmath.c` as C++ and verify that this makes ctype crash:

```
$ g++ -shared -fPIC basics/dullmath.c -o libdullmath.so
$ python
>>> import ctypes
>>> lib = ctypes.CDLL(f'./libdullmath.so')
>>> lib.fibonacci
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "/usr/lib/python3.8/ctypes/__init__.py", line 386, in __getattr__
    func = self.__getitem__(name)
  File "/usr/lib/python3.8/ctypes/__init__.py", line 391, in __getitem__
    func = self._FuncPtr((name_or_ordinal, self))
AttributeError: /home/.../libsimple.so: undefined symbol: fibonacci
```

In order to fix in, `extern "C"` needs to be declared.
Correct C++ code is already located in dullmath.cpp:

```
$ g++ -shared -fPIC dullmath.cpp -o libdullmath.so
$ python
>>> import ctypes
>>> lib = ctypes.CDLL(f'./libdullmath.so')
>>> lib.fibonacci
<_FuncPtr object at 0x7f3aef7eb040>
>>> lib.fibonacci(10)
55
```