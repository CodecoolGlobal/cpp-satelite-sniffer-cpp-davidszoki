#include <PythonScriptConverter.h>
#include <iostream>
#include <filesystem>

using namespace std;

namespace PythonScriptConverter {
    static const filesystem::path workingDirectory = filesystem::current_path().parent_path();

    PyObject *loadPythonModule(const string &moduleName) {
        PyObject *sysPath = PySys_GetObject("path");
        PyObject *pPath = PyUnicode_FromString(
            (workingDirectory.parent_path() / "resources" / "PythonScripts").string().c_str());

        PyList_Append(sysPath, pPath);
        Py_DECREF(pPath);

        PyObject *pName = PyUnicode_FromString(moduleName.c_str());
        PyObject *pModule = PyImport_Import(pName);
        Py_DECREF(pName);

        if (pModule == nullptr) {
            PyErr_Print();
            std::cerr << "Failed to load Python module: " << moduleName << std::endl;
        }

        return pModule;
    }
}
