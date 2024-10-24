set(SOURCES
        main.cpp
        PythonScriptConverter.cpp
        PythonScriptExecutor.cpp
        GPS.cpp
        TLE.cpp
)

add_executable(cpp_satelite_sniffer_cpp_davidszoki ${SOURCES})

# Find the Python library and development files
find_package(Python3 REQUIRED COMPONENTS Development)

# Link the Python libraries
target_link_libraries(cpp_satelite_sniffer_cpp_davidszoki Python3::Python)