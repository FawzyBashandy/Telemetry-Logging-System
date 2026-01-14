#include "LogManager.hpp"
#include "LogMessage.hpp"

#include "ConsoleSink.hpp"
#include "FileSink.hpp"

#include <memory>

int main()
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

    return 0;
}
