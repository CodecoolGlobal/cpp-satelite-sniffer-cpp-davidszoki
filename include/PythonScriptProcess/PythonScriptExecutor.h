#pragma once
#include <Python.h>
#include <string>
#include <GPS.h>
#include <TLE.h>

namespace PythonScriptExecutor {
    void getTLEData(PyObject *pModule, const std::string &username, const std::string &password);

    void executeGetTLEDataPythonScript(const std::string &username, const std::string &password);

    GPS executeGetSatelliteGPSPythonScript(const TLE &tle);

    GPS getSatelliteGPS(PyObject *pModule, const TLE &tle);

    GPS getSatelliteGPSAtTimeWindow(PyObject *pModule, const TLE &tle, const std::string &observation_date);

    GPS executeGetSatelliteGPSPAtTimeWindowPythonScript(const TLE &tle, const std::string &time);
}
