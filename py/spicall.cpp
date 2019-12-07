#define PY_SSIZE_T_CLEAN
#include <iostream>
#include <python2.7/Python.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
//    PyObject *pName, *pModule, *pFunc;
    PyObject *pModule;
    PyObject *spiffs, *check_flag;  
    PyObject *pArgs, *pValue;
    int i;

    if (argc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }

    Py_Initialize();
    spiffs = PyUnicode_DecodeUTF7Stateful( argv[1], argc, argv[1], atol(argv*[1]) ) ;
    /* Error checking of pName left out */
    
 //   spiffs = PyUnicode_DecodeUTF7Stateful( c_char, Py_ssize_t, c_char, Py_ssize_t);

    pModule = PyImport_Import(spiffs);
    Py_DECREF(spiffs);

    if (pModule != NULL) {
        check_flag = PyObject_GetAttrString(pModule, argv[2]);
        /* pFunc is a new reference */

        if (check_flag && PyCallable_Check(check_flag)) {
            pArgs = PyTuple_New(argc - 3);
            for (i = 0; i < argc - 3; ++i) {
                pValue = PyLong_FromLong(atoi(argv[i + 3]));
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(check_flag, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(check_flag);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_XDECREF(check_flag);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}
