cmake_minimum_required(VERSION 3.28)

project(cpp_satelite_sniffer_cpp_davidszoki)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        include
        include/UI
        include/PythonScriptProcess
        include/SatelliteSniffer
)

add_subdirectory(source)

