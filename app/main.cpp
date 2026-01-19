#include "LogManager.hpp"
#include "LogMessage.hpp"
#include "FileTelemetrySource.hpp"
#include "ConsoleSink.hpp"
#include "FileSink.hpp"

#include <memory>
void phase1_Trial();
void phase2_Trial();
int main()
{

    //phase1_Trial();
    phase2_Trial();
    return 0;
}
void phase1_Trial()
{
    LogManager logManager;

    // Add sinks
    logManager.addSink(
        std::make_unique<ConsoleSink>(ConsoleSink::Stream::StdOut)
    );

    logManager.addSink(
        std::make_unique<FileSink>("app.log")
    );

    // Create log messages
    logManager.pushMessage(LogMessage{
        "MyApp",
        "Startup",
        eLogSeverity::Info,
        "Application is starting"
    });

    logManager.pushMessage(LogMessage{
        "MyApp",
        "Config",
        eLogSeverity::Warning,
        "Using default configuration"
    });

    logManager.pushMessage(LogMessage{
        "MyApp",
        "Runtime",
        eLogSeverity::Error,
        "Failed to open database connection"
    });

    // Route buffered messages to all sinks
    logManager.flush();
}
void phase2_Trial()
{
    LogManager logManager;
    FileTelemetrySource statFile("/proc/stat");
    FileTelemetrySource meminfoFile("/proc/meminfo");
    std::string data;
    //Open Sources
    statFile.openSource();
    meminfoFile.openSource();

    // Add sinks
    logManager.addSink(
        std::make_unique<ConsoleSink>(ConsoleSink::Stream::StdOut)
    );

    //Read And log Sources
    statFile.readSource(data);
    logManager.pushMessage(LogMessage{
                                            std::string("/proc/stat"),
                                            data,
                                            eLogSeverity::Info,
                                            std::string("Trial")});
    
    meminfoFile.readSource(data);
    logManager.pushMessage(LogMessage{
                                            std::string("/proc/meminfo"),
                                            data,
                                            eLogSeverity::Info,
                                            std::string("Trial")});
    logManager.flush();
}