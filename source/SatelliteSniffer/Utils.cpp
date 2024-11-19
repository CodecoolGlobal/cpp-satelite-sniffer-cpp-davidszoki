#include <iomanip>
#include <iostream>
#include <string>
#include <Utils.h>

using namespace std;
using namespace chrono;


namespace Utils {
    string getTimeString(const int &milliseconds) {
        tm *time = getLocalTime(milliseconds);

        ostringstream oss;
        oss << std::put_time(time, "%Y-%m-%d %H:%M:%S");

        string formatted_time = oss.str();
        return formatted_time;
    }

    void printLine(const string &message) {
        cout << message << endl;
    }

    void printGPS(const GPS &gps) {
        cout << "Lat: " << gps.latitude << endl;
        cout << "Long: " << gps.longitude << endl;
        cout << "Alt: " << gps.altitude << endl;
    }

    tm *getLocalTime(const int &milliseconds) {
        auto evaulateTime = current + std::chrono::milliseconds(milliseconds);
        auto convertTime = system_clock::to_time_t(evaulateTime);
        tm *time = std::localtime(&convertTime);
        return time;
    }
}