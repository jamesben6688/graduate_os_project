#include <python2.7/Python.h>
#include <stdlib.h>
int main()
{
   // Set PYTHONPATH TO working directory
   setenv("PYTHONPATH",".",1);

   PyObject *pName, *pModule, *pDict, *pFunc1, *pFunc2, *pValue, *presult;


   // Initialize the Python Interpreter
   Py_Initialize();


   // Build the name object
   pName = PyString_FromString((char*)"spiffs");

   // Load the module object
   pModule = PyImport_Import(pName);


   // pDict is a borrowed reference
   pDict = PyModule_GetDict(pModule);


   // pFunc is also a borrowed reference
   pFunc1 = PyDict_GetItemString(pDict, (char*)"check_flag");
   PyErr_Print();
   pFunc2 = PyDict_GetItemString(pDict, (char*)"move_data");
   PyErr_Print();

   if (PyCallable_Check(pFunc1))
   {
       pValue=Py_BuildValue("(z)",(char*)"check_flag");
       PyErr_Print();
       printf("Let's give this a shot!\n");
      // presult=PyObject_CallObject(pFunc,pValue);
      presult = pFunc1;
      // PyErr_Print();
   } else
   {
       PyErr_Print();
   }
   printf("Result is %ld\n",PyInt_AsLong(presult));
   Py_DECREF(pValue);

   // Clean up
   Py_DECREF(pModule);
   Py_DECREF(pName);

   // Finish the Python Interpreter
   Py_Finalize();


    return 0;
}
