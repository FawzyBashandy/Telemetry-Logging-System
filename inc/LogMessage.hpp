#pragma once
#include <chrono>
#include <string>
#include <ostream>
enum class eLogSeverity { Debug, Info, Warning, Error, Fatal };

class LogMessage {
  using TimePoint = std::chrono::system_clock::time_point;

private:
  std::string appName_;
  std::string context_;
  TimePoint timeStamp_;
  eLogSeverity severity_;
  std::string description_;

public:
  LogMessage() = delete;
  LogMessage(std::string appName, 
             std::string context,
             eLogSeverity severity,
             std::string description,
             TimePoint timestamp = std::chrono::system_clock::now());
  
  // Special Functions
  LogMessage(const LogMessage&) = default;
  LogMessage(LogMessage&&) = default;
  LogMessage& operator=(const LogMessage&)=default;
  LogMessage& operator=(LogMessage&&)=default;
  
  // Getters (const-correct)
  const std::string& getAppName() const;
  const std::string& getContext() const;
  const std::string& getText() const;
  eLogSeverity getSeverity() const;
  TimePoint getTimestamp() const;
  //String Formatter
  friend std::ostream& operator<<(std::ostream& os,const LogMessage& msg);
  ~LogMessage() = default;
};