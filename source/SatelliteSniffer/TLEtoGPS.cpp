#include <fstream>
#include <PythonScriptExecutor.h>
#include <TLEtoGPS.h>
#include <Utils.h>

using namespace std;

namespace TLEtoGPS {
    TLE readTLEData(const string &filename) {
        TLE tle = {"", ""};
        ifstream file(workingDirectory / "../resources/TLE/" / filename);

        if (!file.is_open()) {
            Utils::printLine("Error opening file: " + filename);
            return tle;
        }

        string line1, line2;
        while (getline(file, line1) && getline(file, line2)) {
            {
                tle.tle_line1 = line1;
                tle.tle_line2 = line2;
            }
        }

        file.close();
        return tle;
    }

    GPS convertTLEToGPS(const string &filename) {
        const auto tle = readTLEData(filename);
        return PythonScriptExecutor::executeGetSatelliteGPSPythonScript(tle);
    }

    GPS convertTLEToGPSAtTimeWindow(const string &filename, const int &millisecs) {
        const auto tle = readTLEData(filename);
        const auto timeString = Utils::getTimeString(millisecs);
        return PythonScriptExecutor::executeGetSatelliteGPSPAtTimeWindowPythonScript(tle, timeString);
    }
}
