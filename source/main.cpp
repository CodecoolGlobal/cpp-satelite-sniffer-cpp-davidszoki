#include <UI.h>
#include <TLEtoGPS.h>
#include <Utils.h>
#include <PythonScriptExecutor.h>

using namespace std;

int main(int argc, char *argv[]) {
    PythonScriptExecutor::executeGetTLEDataPythonScript(getenv("USERNAME"), getenv("PASSWORD"));
    //auto gps = TLEtoGPS::convertTLEToGPS("iss_last_tle.txt");
    auto gps2 = TLEtoGPS::convertTLEToGPSAtTimeWindow("iss_last_tle.txt");
    auto gps3 = TLEtoGPS::convertTLEToGPSAtTimeWindow("iss_last_tle.txt", 1000);
    auto gps4 = TLEtoGPS::convertTLEToGPSAtTimeWindow("iss_last_tle.txt", 10000);

    //Utils::printGPS(gps);
    Utils::printGPS(gps2);
    Utils::printGPS(gps3);
    Utils::printGPS(gps4);

    UI ui;
    ui.run();

    return 0;
}
