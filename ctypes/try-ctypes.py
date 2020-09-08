# Color output
GREEN = '\033[92m'
RED = '\033[91m'
DEF = '\033[0m'

def print_colored(color=DEF, text=''):
    print(color + text + DEF)



import ctypes

lib = ctypes.CDLL(f'./libdullmath.so')
print_colored(GREEN, '## Library loaded: ')
print(lib)
# <CDLL './libdullmath.so', handle 5568806f63b0 at 0x7f55d9d52dc0>

print_colored(GREEN, '## lib.get_pi: ')
print(lib.get_pi)
# <_FuncPtr object at 0x7f3671537b80>

print_colored(GREEN, '## lib.fibonacci: ')
print(lib.fibonacci)
# <_FuncPtr object at 0x7f3671537700>

print_colored(RED, '## lib.other_function: ')
try:
    print(lib.other_function)
except AttributeError:
    import traceback
    traceback.print_exc()
# Traceback (most recent call last):
#   File "<stdin>", line 1, in <module>
#   File "/usr/lib/python3.8/ctypes/__init__.py", line 386, in __getattr__
#     func = self.__getitem__(name)
#   File "/usr/lib/python3.8/ctypes/__init__.py", line 391, in __getitem__
#     func = self._FuncPtr((name_or_ordinal, self))
# AttributeError: /home/.../libsimple.so: undefined symbol: other_function

print_colored(GREEN, '\n## RUNNING FUNCTIONS:')
print(">>> [lib.fibonacci(i) for i in range(7)]")
print([lib.fibonacci(i) for i in range(7)])
# [0, 1, 1, 2, 3, 5, 8])

print(">>> lib.get_pi()")
print(lib.get_pi())
# 0
print("\n>>> lib.get_pi.restype = ctypes.c_float")
lib.get_pi.restype = ctypes.c_float
print(">>> lib.get_pi()")
print(lib.get_pi())
# 3.140000104904175
