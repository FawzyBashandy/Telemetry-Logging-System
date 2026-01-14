#include "LogMessage.hpp"
#include <ctime>
#include <iomanip>
LogMessage::LogMessage(std::string appName, std::string context,
                       eLogSeverity severity, std::string description,
                       TimePoint timestamp = std::chrono::system_clock::now())
    : appName_(std::move(appName)), context_(std::move(context)),
      severity_(severity), description_(std::move(description)),
      timeStamp_(timestamp) 
      {

      }
const std::string& LogMessage::getAppName() const {
  return appName_;
}
const std::string& LogMessage::getContext() const {
  return context_;
}

const std::string& LogMessage::getText() const {
  return description_;
}
eLogSeverity LogMessage::getSeverity() const {
    return severity_;
}
LogMessage::TimePoint LogMessage::getTimestamp() const {
    return timeStamp_;
}

std::ostream& operator<<(std::ostream& os, const LogMessage& msg)
{
    // Convert timestamp
    std::time_t time =
        std::chrono::system_clock::to_time_t(msg.timeStamp_);

    os << "[" << std::put_time(std::localtime(&time),
                               "%Y-%m-%d %H:%M:%S") << "] "
       << "[" << msg.appName_ << "] "
       << "[" << msg.context_ << "] "
       << "[" << severityToString(msg.severity_) << "] "
       << msg.description_;

    return os;
}

//Helper
const char* severityToString(eLogSeverity s)
{
    switch (s)
    {
        case eLogSeverity::Debug:   return "DEBUG";
        case eLogSeverity::Info:    return "INFO";
        case eLogSeverity::Warning: return "WARNING";
        case eLogSeverity::Error:   return "ERROR";
        case eLogSeverity::Fatal:   return "FATAL";
        default:                    return "UNKNOWN";
    }
}
