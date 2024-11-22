#pragma once
#include <Python.h>
#include <filesystem>
#include <string>
#include <GPS.h>
#include <TLE.h>

static const std::filesystem::path workingDirectory = std::filesystem::current_path().parent_path();

namespace PythonScriptExecutor {
    void getTLEData(PyObject *pModule, const std::string &username, const std::string &password,
                    const std::string &satelliteName, const std::string &noradId);

    void executeGetTLEDataPythonScript(const std::string &username, const std::string &password, const std::string &filename);

    GPS executeGetSatelliteGPSPythonScript(const TLE &tle);

    GPS getSatelliteGPS(PyObject *pModule, const TLE &tle);

    GPS getSatelliteGPSAtTimeWindow(PyObject *pModule, const TLE &tle, const std::string &observation_date);

    GPS executeGetSatelliteGPSPAtTimeWindowPythonScript(const TLE &tle, const std::string &time);
}
