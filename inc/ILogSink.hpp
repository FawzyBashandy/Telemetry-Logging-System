#pragma once
#include <string>
class ILogSink
{
public:
    virtual ~ILogSink() = default;

    virtual void write(const std::string& message) = 0;
};