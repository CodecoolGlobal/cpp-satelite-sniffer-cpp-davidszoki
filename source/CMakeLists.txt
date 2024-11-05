set(SOURCES
        main.cpp
        PythonScriptConverter.cpp
        PythonScriptExecutor.cpp
        GPS.cpp
        TLE.cpp
)

add_executable(cpp_satelite_sniffer_cpp_davidszoki ${SOURCES})

find_package(Python3 REQUIRED COMPONENTS Development)

target_link_libraries(cpp_satelite_sniffer_cpp_davidszoki
        PRIVATE
        Python3::Python
)