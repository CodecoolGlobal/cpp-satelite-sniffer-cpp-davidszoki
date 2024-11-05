set(SOURCES
        main.cpp
        PythonScriptProcess/PythonScriptConverter.cpp
        PythonScriptProcess/PythonScriptExecutor.cpp
        SatelliteSniffer/GPS.cpp
        SatelliteSniffer/TLE.cpp
        UI/UI.cpp
        UI/Texture.cpp
)

add_executable(cpp_satelite_sniffer_cpp_davidszoki ${SOURCES})

find_package(Python3 REQUIRED COMPONENTS Development)

target_link_libraries(cpp_satelite_sniffer_cpp_davidszoki
        PRIVATE
        Python3::Python
)