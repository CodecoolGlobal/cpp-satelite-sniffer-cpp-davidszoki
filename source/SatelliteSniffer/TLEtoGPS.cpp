#include <fstream>
#include <PythonScriptExecutor.h>
#include <TLEtoGPS.h>
#include <Utils.h>

using namespace std;

namespace TLEtoGPS {
    TLE readTLEData(const string &filename) {
        TLE tle = {"", "", ""};
        ifstream file(workingDirectory / "../resources/TLE/" / filename);

        if (!file.is_open()) {
            Utils::printLine("Error opening file: " + filename);
            return tle;
        }

        size_t lastDot = filename.find_last_of('.');
        if (lastDot != string::npos) {
            tle.name = filename.substr(0, lastDot);
        } else {
            tle.name = filename;
        }

        string line1, line2;
        while (getline(file, line1) && getline(file, line2)) {
            {
                tle.line1 = line1;
                tle.line2 = line2;
            }
        }

        file.close();
        return tle;
    }

    GPS convertTLEToGPS(const string &filename) {
        const auto tle = readTLEData(filename);
        return PythonScriptExecutor::executeGetSatelliteGPSPythonScript(tle);
    }
}
