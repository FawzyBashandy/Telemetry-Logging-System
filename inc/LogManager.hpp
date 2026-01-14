#pragma once
#include <vector>
#include <memory>

#include "ILogSink.hpp"
#include "LogMessage.hpp"

class LogManager {
    public:
    LogManager()=default;
    // non-copyable (manager owns sinks)
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    // movable
    LogManager(LogManager&&) = default;
    LogManager& operator=(LogManager&&) = default;

    void addSink(std::unique_ptr<ILogSink> sink);

    void pushMessage(LogMessage msg);
    //Route Messages to all Sinks
    void flush();
    
    private:
    std::vector<LogMessage> messages_;
    std::vector<std::unique_ptr<ILogSink>> sinks_;
};