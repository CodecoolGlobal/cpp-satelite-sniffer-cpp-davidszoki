#include <iostream>
#include <PythonScriptExecutor.h>
#include <UI.h>

using namespace std;

int main(int argc, char *argv[]) {
    PythonScriptExecutor::executeGetTLEDataPythonScript(getenv("USERNAME"), getenv("PASSWORD"));
    auto tle = TLE("1 25544U 98067A   24295.97717271  .00019869  00000-0  35261-3 0  9996",
                   "2 25544  51.6397  47.3842 0009127  92.3206 267.8828 15.50175955478218");
    const auto gps = PythonScriptExecutor::executeGetSatelliteCoordinatesPythonScript(tle);

    cout << gps.latitude << endl;
    cout << gps.longtitude << endl;
    cout << gps.altitude << endl;

    UI ui;
    ui.run(2);
    return 0;
}
