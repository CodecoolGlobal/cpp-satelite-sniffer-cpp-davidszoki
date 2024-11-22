#include <TLE.h>

using namespace std;

TLE::TLE(const std::string &tle_name, const string &tle_line1, const string &tle_line2) : name(tle_name),
    line1(tle_line1),
    line2(tle_line2) {
}
