#include "PythonScriptExecutor.h"
#include <PythonScriptConverter.h>
#include <iostream>


using namespace std;

namespace PythonScriptExecutor {
    void executeGetTLEDataPythonScript(const string &username, const string &password) {
        Py_Initialize();
        auto pModule = PythonScriptConverter::loadPythonModule("GetTLE");
        getTLEData(pModule, username, password);
        Py_Finalize();
    }

    void getTLEData(PyObject *pModule, const string &username, const string &password) {
        if (pModule != nullptr) {
            PyObject *pFunc = PyObject_GetAttrString(pModule, "fetch_tle_data");

            if (pFunc && PyCallable_Check(pFunc)) {
                PyObject *pUsername = PyUnicode_FromString(username.c_str());
                PyObject *pPassword = PyUnicode_FromString(password.c_str());

                PyObject *pArgs = PyTuple_Pack(2, pUsername, pPassword);
                PyObject *pValue = PyObject_CallObject(pFunc, pArgs);

                Py_DECREF(pArgs);
                Py_DECREF(pUsername);
                Py_DECREF(pPassword);

                if (pValue != nullptr) {
                    if (PyUnicode_Check(pValue)) {
                        cout << "Python function returned:" << endl << PyUnicode_AsUTF8(pValue) << endl;
                    } else {
                        cerr << "Unexpected return type from fetch_tle_data" << endl;
                    }
                    Py_DECREF(pValue);
                } else {
                    PyErr_Print();
                    cerr << "Call to fetch_tle_data() failed!" << endl;
                }

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

    GPS executeGetSatelliteCoordinatesPythonScript(const TLE &tle) {
        Py_Initialize();
        auto pModule = PythonScriptConverter::loadPythonModule("TLEtoGPS");
        auto gps = getSatelliteCoordinates(pModule, tle);
        Py_Finalize();
        return gps;
    }

    GPS getSatelliteCoordinates(PyObject *pModule, const TLE &tle) {
        GPS gpsData{0, 0, 0};

        if (pModule != nullptr) {
            PyObject *pFunc = PyObject_GetAttrString(pModule, "get_satellite_coordinates");

            if (pFunc && PyCallable_Check(pFunc)) {
                PyObject *pTleName = PyUnicode_FromString(tle.tle_name.c_str());
                PyObject *pTleLine1 = PyUnicode_FromString(tle.tle_line1.c_str());
                PyObject *pTleLine2 = PyUnicode_FromString(tle.tle_line2.c_str());

                PyObject *pArgs = PyTuple_Pack(3, pTleName, pTleLine1, pTleLine2);
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
    GPS getSatelliteGPSAtTimeWindow(PyObject *pModule, const TLE &tle, const string &observation_date) {
        GPS gpsData{0, 0, 0};

        if (pModule != nullptr) {
            PyObject *pFunc = PyObject_GetAttrString(pModule, "get_satellite_gps_at_time_window");

            if (pFunc && PyCallable_Check(pFunc)) {
                PyObject *pTleName = PyUnicode_FromString(tle.tle_name.c_str());
                PyObject *pTleLine1 = PyUnicode_FromString(tle.tle_line1.c_str());
                PyObject *pTleLine2 = PyUnicode_FromString(tle.tle_line2.c_str());
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
