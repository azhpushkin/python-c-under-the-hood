#cython: language_level=3
cpdef int fibonacci(int n):
    if n <= 0: return 0
    if n == 1: return 1
    return fibonacci(n-1) + fibonacci(n-2)

cpdef float get_pi():
    return 3.14
