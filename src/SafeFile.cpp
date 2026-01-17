#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "SafeFile.hpp"

SafeFile::SafeFile(const std::string& filePath)
{
    fd_ = open(filePath.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd_ < 0)
    {
        throw std::runtime_error("Failed To open Log File !");
    }
}
SafeFile::~SafeFile()
{
    if(fd_ >= 0)
    {
        close(fd_);
        fd_=-1;
    }
}
SafeFile::SafeFile(SafeFile && other)
{
    fd_ = other.fd_;
    other.fd_ = -1; //Reset FD
}
SafeFile& SafeFile::operator=(SafeFile && other)
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
void SafeFile::write(const std::string& message)
{
    ::write(fd_,message.c_str(),message.size()); // ::Access Global Scope Write rather than local one
    ::write(fd_,"\n",1);
}
