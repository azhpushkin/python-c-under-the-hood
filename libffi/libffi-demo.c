#include <stdio.h>
#include <dlfcn.h>
#include <ffi.h>

int main()
{
    void* dullmath = dlopen("./libdullmath.so", RTLD_LAZY);
    if (!dullmath) return 1;

    // We use void* to pretend the function type
    // is unknown at compile-time
    void* fibonacci_ptr  = dlsym(dullmath, "fibonacci");
    if (!fibonacci_ptr) return 2;
  
    // Describe arguments and return value of function
    ffi_type* atypes[] = {&ffi_type_sint};
    ffi_type* rtype = &ffi_type_sint;
  
    // Initialize Call InterFace
    ffi_cif cif;
    ffi_status status = ffi_prep_cif(
        &cif, FFI_DEFAULT_ABI,
        1, rtype, atypes  // number of args and their types
    );

    int result;  // storage for result value
    for (int i = 5; i < 10; i++){
        // `ffi_call` can modify call arguments, so copy
        // loop-counter to avoid modification of original value
        int j = i;
        void* call_args[] = {&j};
         
        ffi_call(&cif, FFI_FN(fibonacci_ptr), &result, call_args);
        printf("fib(%d) is %d\n", i, result);
    }
 
    return 0;
}