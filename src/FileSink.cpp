#include <FileSink.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>

FileSink::FileSink(const std::string& path)
{
    _sinkFile.open(path,FileMode::WriteAppend);
}

void FileSink::write(const std::string& message)
{
    _sinkFile.write(message);
}
