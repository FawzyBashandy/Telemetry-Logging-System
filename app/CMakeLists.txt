set(targetMachine ) # Add any target machine specific flags if needed
set(libName TelemetryLogSystemLib)

add_executable(app ${targetMachine} main.cpp)

target_link_libraries(app PRIVATE ${libName})

message(STATUS "Executable Created and Linked with Library !")
