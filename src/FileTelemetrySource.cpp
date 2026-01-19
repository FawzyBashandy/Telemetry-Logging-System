#include <iostream>
#include "FileTelemetrySource.hpp"
FileTelemetrySource::FileTelemetrySource(const std::string& path) : _path{path}
{

}
bool FileTelemetrySource::openSource()
{
    return _sFile.open(_path,FileMode::ReadOnly);
}
bool FileTelemetrySource::readSource(std::string& out)
{
    return _sFile.readLine(out); //....
}
