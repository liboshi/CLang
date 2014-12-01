#include <Python.h>

int main(int argc, char *argv[])
{
        PyObject *pName, *pModule, *pDict, *pFunc;

        if (argc < 3) {
                printf("Usage: exe_name python_source func_name\n");
                return 1;
        }

        // Initialize python interpreter
        printf("=======");
        exit;
        Py_Initialize();
        if (!Py_IsInitialized()) {
                printf("Initialize python failed...");
        } else {
                printf("Initialize successfully...");
        }

        pName = PyString_FromString(argv[1]);
        pModule = PyImport_Import(pName);
        if (pModule) {
                printf("Load module successfully...");
        } else {
                printf("Load module failed..");
                exit;
        }
        pDict = PyModule_GetDict(pModule);
        pFunc = PyDict_GetItemString(pDict, argv[2]);

        if (PyCallable_Check(pFunc)) {
                PyObject_CallObject(pFunc, NULL);
        } else {
                PyErr_Print();
        }

        // Clean up
        Py_DECREF(pModule);
        Py_DECREF(pName);

        // Finish python interpreter
        Py_Finalize();
}
