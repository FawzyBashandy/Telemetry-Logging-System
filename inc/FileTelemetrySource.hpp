#pragma once
#include <iostream>
#include "ITelemetrySource.hpp"
#include "SafeFile.hpp"
class FileTelemetrySource final : public ITelemetrySource
{   
    public:
    explicit FileTelemetrySource(const std::string& path);
    bool openSource() override;
    bool readSource(std::string& out) override;
    ~FileTelemetrySource() override =default;
    
    private:
    SafeFile _sFile;
    std::string _path;
};