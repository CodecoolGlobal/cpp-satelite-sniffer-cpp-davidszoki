#pragma once
#include <Python.h>
#include <string>
#include <GPS.h>
#include <TLE.h>

namespace PythonScriptExecutor {
    void executeGetTLEDataPythonScript(const std::string &username, const std::string &password);

    void getTLEData(PyObject *pModule, const std::string &username, const std::string &password);

    GPS executeGetSatelliteCoordinatesPythonScript(const TLE &tle);

    GPS getSatelliteCoordinates(PyObject *pModule, const TLE &tle);
    GPS getSatelliteGPSAtTimeWindow(PyObject *pModule, const TLE &tle, const std::string &observation_date);
}
