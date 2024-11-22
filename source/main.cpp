#include <SatelliteSniffer.h>

using namespace std;

int main(int argc, char *argv[]) {
    auto satelliteSniffer = SatelliteSniffer("Satellites.txt", 1024, 512);
    satelliteSniffer.run();
    return 0;
}
