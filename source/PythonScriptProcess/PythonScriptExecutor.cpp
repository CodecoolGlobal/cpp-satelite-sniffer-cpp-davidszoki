#include "PythonScriptExecutor.h"
#include <fstream>
#include <PythonScriptConverter.h>
#include <iostream>
#include <sstream>
#include <Utils.h>

using namespace std;

namespace PythonScriptExecutor {
    void getTLEData(PyObject *pModule, const string &username, const string &password, const string &filePath) {
        if (pModule != nullptr) {
            PyObject *pFunc = PyObject_GetAttrString(pModule, "fetch_tle_data");

            if (pFunc && PyCallable_Check(pFunc)) {
                // Open the satellite data file
                ifstream inputFile(filePath);
                if (!inputFile.is_open()) {
                    cerr << "Failed to open file: " << filePath << endl;
                    Py_DECREF(pFunc);
                    Py_DECREF(pModule);
                    return;
                }

                string line;
                while (getline(inputFile, line)) {
                    // Parse satellite name and NORAD ID from the line
                    stringstream ss(line);
                    string name, noradIdStr;
                    if (!getline(ss, name, ';') || !getline(ss, noradIdStr)) {
                        cerr << "Invalid line format: " << line << endl;
                        continue;
                    }

                    // Call the Python function fetch_tle_data
                    PyObject *pUsername = PyUnicode_FromString(username.c_str());
                    PyObject *pPassword = PyUnicode_FromString(password.c_str());
                    PyObject *pName = PyUnicode_FromString(name.c_str());
                    PyObject *pNoradId = PyUnicode_FromString(noradIdStr.c_str());

                    PyObject *pArgs = PyTuple_Pack(4, pUsername, pPassword, pName, pNoradId);
                    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);

                    Py_DECREF(pArgs);
                    Py_DECREF(pUsername);
                    Py_DECREF(pPassword);
                    Py_DECREF(pName);
                    Py_DECREF(pNoradId);

                    if (pValue != nullptr) {
                        if (PyUnicode_Check(pValue)) {
                            cout << "Python function returned for " << name << ":" << endl
                                    << PyUnicode_AsUTF8(pValue) << endl;
                        } else {
                            cerr << "Unexpected return type from fetch_tle_data for " << name << endl;
                        }
                        Py_DECREF(pValue);
                    } else {
                        PyErr_Print();
                        cerr << "Call to fetch_tle_data() failed for " << name << endl;
                    }
                }

                inputFile.close();
                Py_DECREF(pFunc);
            } else {
                if (PyErr_Occurred()) PyErr_Print();
                cerr << "Cannot find function 'fetch_tle_data'" << endl;
            }

            Py_DECREF(pModule);
        } else {
            PyErr_Print();
            cerr << "Failed to load Python module 'GetTLE'" << endl;
        }
    }

    void executeGetTLEDataPythonScript(const string &username, const string &password, const string &filename) {
        Py_Initialize();
        auto pModule = PythonScriptConverter::loadPythonModule("GetTLE");
        auto filePath = workingDirectory / "../resources/Satellites/" / filename;
        getTLEData(pModule, username, password, filePath.u8string());
        Py_Finalize();
    }

    GPS getSatelliteGPS(PyObject *pModule, const TLE &tle) {
        GPS gpsData{0, 0, 0};

        if (pModule != nullptr) {
            PyObject *pFunc = PyObject_GetAttrString(pModule, "get_satellite_gps");

            if (pFunc && PyCallable_Check(pFunc)) {
                PyObject *pTleLine1 = PyUnicode_FromString(tle.line1.c_str());
                PyObject *pTleLine2 = PyUnicode_FromString(tle.line2.c_str());

                PyObject *pArgs = PyTuple_Pack(2, pTleLine1, pTleLine2);
                PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
                Py_DECREF(pArgs);
                Py_DECREF(pTleLine1);
                Py_DECREF(pTleLine2);

                if (pValue != nullptr) {
                    if (PyTuple_Check(pValue) && PyTuple_Size(pValue) == 3) {
                        double latitude = PyFloat_AsDouble(PyTuple_GetItem(pValue, 0));
                        double longitude = PyFloat_AsDouble(PyTuple_GetItem(pValue, 1));
                        double altitude = PyFloat_AsDouble(PyTuple_GetItem(pValue, 2));

                        gpsData = GPS(latitude, longitude, altitude);
                    } else {
                        std::cerr << "Returned value is not a tuple!" << std::endl;
                    }
                    Py_DECREF(pValue);
                } else {
                    PyErr_Print();
                    std::cerr << "Call to get_satellite_coordinates() failed!" << std::endl;
                }
                Py_DECREF(pFunc);
            } else {
                std::cerr << "Cannot find function get_satellite_coordinates!" << std::endl;
            }
        }

        return gpsData;
    }

    GPS executeGetSatelliteGPSPythonScript(const TLE &tle) {
        Py_Initialize();
        auto pModule = PythonScriptConverter::loadPythonModule("TLEtoGPS");
        auto gps = getSatelliteGPS(pModule, tle);
        Py_Finalize();
        return gps;
    }

    GPS getSatelliteGPSAtTimeWindow(PyObject *pModule, const TLE &tle, const string &observation_date) {
        GPS gpsData{0, 0, 0};

        if (pModule != nullptr) {
            PyObject *pFunc = PyObject_GetAttrString(pModule, "get_satellite_gps_at_time_window");

            if (pFunc && PyCallable_Check(pFunc)) {
                PyObject *pTleName = PyUnicode_FromString(tle.name.c_str());
                PyObject *pTleLine1 = PyUnicode_FromString(tle.line1.c_str());
                PyObject *pTleLine2 = PyUnicode_FromString(tle.line2.c_str());
                PyObject *pObsDate = PyUnicode_FromString(observation_date.c_str());

                PyObject *pArgs = PyTuple_Pack(4, pObsDate, pTleName, pTleLine1, pTleLine2);
                PyObject *pValue = PyObject_CallObject(pFunc, pArgs);

                Py_DECREF(pArgs);
                Py_DECREF(pObsDate);
                Py_DECREF(pTleName);
                Py_DECREF(pTleLine1);
                Py_DECREF(pTleLine2);

                if (pValue != nullptr) {
                    if (PyTuple_Check(pValue) && PyTuple_Size(pValue) == 3) {
                        double latitude = PyFloat_AsDouble(PyTuple_GetItem(pValue, 0));
                        double longitude = PyFloat_AsDouble(PyTuple_GetItem(pValue, 1));
                        double altitude = PyFloat_AsDouble(PyTuple_GetItem(pValue, 2));

                        gpsData = GPS(latitude, longitude, altitude);
                    } else {
                        std::cerr << "Returned value is not a tuple!" << std::endl;
                    }
                    Py_DECREF(pValue);
                } else {
                    PyErr_Print();
                    std::cerr << "Call to get_satellite_position() failed!" << std::endl;
                }
                Py_DECREF(pFunc);
            } else {
                std::cerr << "Cannot find function get_satellite_position!" << std::endl;
            }
        }

        return gpsData;
    }

    GPS executeGetSatelliteGPSPAtTimeWindowPythonScript(const TLE &tle, const string &time) {
        Py_Initialize();
        auto pModule = PythonScriptConverter::loadPythonModule("TLEtoGPS");
        auto gps = getSatelliteGPSAtTimeWindow(pModule, tle, time);
        Py_Finalize();
        return gps;
    }
}
