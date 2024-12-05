set(SOURCES
        main.cpp
        PythonScriptProcess/PythonScriptConverter.cpp
        PythonScriptProcess/PythonScriptExecutor.cpp
        SatelliteSniffer/GPS.cpp
        SatelliteSniffer/TLE.cpp
        UI/UI.cpp
        UI/Texture.cpp
        SatelliteSniffer/Utils.cpp
        SatelliteSniffer/SatelliteSniffer.cpp
        SatelliteSniffer/Satellite.cpp
)

add_executable(cpp_satelite_sniffer_cpp_davidszoki ${SOURCES})

find_package(Python3 REQUIRED COMPONENTS Development)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

target_link_libraries(cpp_satelite_sniffer_cpp_davidszoki
        PRIVATE
        Python3::Python
        SDL2::SDL2main
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf)