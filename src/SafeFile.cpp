#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "SafeFile.hpp"

SafeFile::~SafeFile()
{
    if(fd_ >= 0)
    {
        close();
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
        close();

        fd_ = other.fd_;
        other.fd_ = -1;
    }
    return *this;
}
bool SafeFile::open(const std::string& path, FileMode mode) {
    close(); // close any existing fd
    if(mode == FileMode::WriteAppend)
    fd_ = ::open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
    fd_ = ::open(path.c_str(), O_RDONLY);
    return fd_ != -1;
}
void SafeFile::close()
{
    if(fd_ !=-1)
    {
        ::close(fd_);
        fd_=-1;
    }
}
bool SafeFile::write(const std::string& message)
{
    if (fd_ == -1) {
        return false;
    }

    ssize_t written = ::write(fd_, message.c_str(), message.size());
    if (written != static_cast<ssize_t>(message.size())) {
        return false;
    }

    if (::write(fd_, "\n", 1) != 1) {
        return false;
    }

    return true;
}

bool SafeFile::readLine(std::string& out)
{
    out.clear();
    char ch;

    while (true) {
        ssize_t bytes = ::read(fd_,&ch, 1);

        if (bytes <= 0) {
            return !out.empty(); // allow last partial line
        }

        if (ch == '\n') {
            return true;
        }

        out.push_back(ch);
    }
}
