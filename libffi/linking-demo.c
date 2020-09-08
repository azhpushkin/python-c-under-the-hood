#include <dlfcn.h>  // header for libdl
#include <stdio.h>

int main(void)
{   
  // dlopen loads shared library to memory by path
  void* lib = dlopen("./libdullmath.so", RTLD_LAZY);
  if (!lib) return 1;
  
  // dlsym finds function by symbols
  int (*fibonacci)(int)  = dlsym(lib, "fibonacci");
  if (!fibonacci) return 2;
  
  for (int i = 5; i < 10; i++)
    printf("fibonacci(%d) = %d\n", i, fibonacci(i));
  
  return 0;
}