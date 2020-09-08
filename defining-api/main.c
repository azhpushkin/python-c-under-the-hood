#include <dlfcn.h>
#include <stdio.h>

int main(void)
{   
    char libname[20], funcname[20];
    printf("Enter library name and function: ");
    scanf("%s %s", libname, funcname);
    
    void * lib = dlopen(libname, RTLD_LAZY);  // load library
    if (!lib) return 1;
    
    // NOTE: fun_ptr signature is hardcoded as (int) -> int
    int (*fun_ptr)(int)  = dlsym(lib, funcname);
    if (!fun_ptr) return 2;
    
    printf("%s(x), x:0-9\n>>>  ");
    for (int i = 0; i < 10; i++)
      printf("%d ", fun_ptr(i));
    
    printf("\n");
    return 0;
}