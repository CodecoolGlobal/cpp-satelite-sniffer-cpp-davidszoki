#include <fstream>
#include <iomanip>
#include <iostream>
#include <PythonScriptExecutor.h>
#include <Satellite.h>
#include <Utils.h>

using namespace std;
using namespace chrono;


namespace Utils {
    string getTimeString(const int &milliseconds) {
        tm *time = getGMTTime(milliseconds);

        ostringstream oss;
        oss << std::put_time(time, "%Y-%m-%d %H:%M:%S");

        string formatted_time = oss.str();
        return formatted_time;
    }

    void printLine(const string &message) {
        cout << message << endl;
    }

    void printLine(const string &message0, const string &message1) {
        cout << message0<< message1 << endl;
    }

    void printGPS(const GPS &gps) {
        cout << "Lat: " << gps.latitude << endl;
        cout << "Long: " << gps.longitude << endl;
        cout << "Alt: " << gps.altitude << endl;
    }

    tm *getGMTTime(const int &milliseconds) {
        auto evaulateTime = current + std::chrono::milliseconds(milliseconds);
        auto convertTime = system_clock::to_time_t(evaulateTime);
        tm *time = gmtime(&convertTime);
        return time;
    }

    void fillSatellitesBySourceFile(const string &filename, vector<Satellite> &satellites) {
        auto path = workingDirectory / "../resources/Satellites/" / filename;
        ifstream inputFile(path);

        if (!inputFile.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
        }

        string line;
        while (std::getline(inputFile, line)) {
            stringstream ss(line);
            string name;
            if (getline(ss, name, ';')) {
                satellites.emplace_back(name + ".txt");
            } else {
                cerr << "Invalid line format: " << line << endl;
            }
        }

        inputFile.close();
    }
}
