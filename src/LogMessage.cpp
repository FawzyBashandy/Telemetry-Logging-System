#include "LogMessage.hpp"

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

