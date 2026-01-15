cmake_minimum_required(VERSION 3.10)
project(TelemetryLogSystem)
enable_language(CXX)

add_subdirectory(src)
add_subdirectory(app)



add_custom_command(
    OUTPUT app.map
    COMMAND /usr/bin/objdump -x app/app > app.map
    COMMENT "Custom Command Running"
)
add_custom_target(GenerateMapFile ALL 
    DEPENDS app.map app
    COMMENT "Generating Map File for app.elf")