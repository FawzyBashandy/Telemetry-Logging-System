set(LibraryType STATIC)
add_library(TelemetryLogSystemLib ${LibraryType}
    ConsoleSink.cpp
    FileSink.cpp
    LogManager.cpp
    LogMessage.cpp
    FileTelemetrySource.cpp
    SafeFile.cpp
    SocketTelemetrySource.cpp
)

target_include_directories(TelemetryLogSystemLib PUBLIC ../inc)
message(STATUS "Library Created !")
