#pragma once
#include <string>
#include <Python.h>

namespace PythonScriptConverter {
    PyObject* loadPythonModule(const std::string& moduleName);
}
