#include "LogManager.hpp"

#include <sstream>

void LogManager::addSink(std::unique_ptr<ILogSink> sink)
{
    sinks_.push_back(std::move(sink));
}

void LogManager::pushMessage(LogMessage msg)
{
    messages_.push_back(std::move(msg));
}

void LogManager::flush()
{
    for (const auto& msg : messages_)
    {
        std::ostringstream oss;
        oss << msg;  

        const std::string formatted = oss.str();

        for (const auto& sink : sinks_)
        {
            sink->write(formatted);
        }
    }

    messages_.clear();
}
