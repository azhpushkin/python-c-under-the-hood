#include <Python.h>

long square(long n) {return n * n;}

// Wrapper around pure C function
static PyObject* py_square(PyObject* self, PyObject* args)
{
    long n;
    // parse arguments to ensure only single integer passed
    if (!PyArg_ParseTuple(args, "i", &n))
      return NULL;
    PyObject* res = PyLong_FromLong(square(n));
    return res;
}

// Array of library functions
static PyMethodDef Methods[] = {
    // METH_VARARGS defines variable arguments amount 
    {"square", py_square, METH_VARARGS, "Square an integer"},
    {NULL, NULL, 0, NULL}  /* terminator */
};

// Module metadata wrapper
static struct PyModuleDef mymathmodule = {
    PyModuleDef_HEAD_INIT,
    "mymath",   // name of the module
    NULL,       // documentation string
    -1,         // module state (details at PEP-3121)
    Methods     // functions table
};

// NOTE: entry point function has dynamic name PyInit_<module>
PyMODINIT_FUNC PyInit_mymath(void)
{
    return PyModule_Create(&mymathmodule);
}