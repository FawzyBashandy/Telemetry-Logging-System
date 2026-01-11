#include <FileSink.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>

FileSink::FileSink(const std::string& path)
{
    fd_ = open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd_ < 0)
    {
        throw std::runtime_error("Failed To open Log File !");
    }
}
FileSink::~FileSink()
{
    if(fd_ >= 0)
    {
        close(fd_);
    }
}
void FileSink::write(const std::string& message)
{
    ::write(fd_,message.c_str(),message.size()); // ::Access Global Scope Write rather than local one
    ::write(fd_,"\n",1);
}
FileSink::FileSink(FileSink && other)
{
    fd_ = other.fd_;
    other.fd_ = -1; //Reset FD
}
FileSink & FileSink::operator=(FileSink && other)
{
    if(this != &other)
    {
        //Close my File First
        close(fd_);

        fd_ = other.fd_;
        other.fd_ = -1;
    }
    return *this;
}