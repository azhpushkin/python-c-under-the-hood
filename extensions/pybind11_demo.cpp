#include <pybind11/pybind11.h>

float get_pi() { return 3.14; }

// Macros for generating PyInit_* function and PyModuleDef
// `pybind11_demo` here is required for naming of init function
PYBIND11_MODULE(pybind11_demo, m) {
    m.doc() = "my dull math library";  // module docstring

    m.def(
        "get_pi",  // function name
        &get_pi,  // pointer to function
        "Guess what: returns PI number"  // docstring
    );
}