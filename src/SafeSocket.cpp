#include "SafeSocket.hpp"
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

SafeSocket::SafeSocket() {
    sockfd_ = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if(sockfd_ < 0)
    {
        throw std::runtime_error("Socket Openning Failed!");
    }
}
void SafeSocket::close()
{
    if(sockfd_ >= 0)
    {
        ::close(sockfd_);
        sockfd_ = -1;
    }
}
SafeSocket::SafeSocket(SafeSocket&& other): sockfd_(other.sockfd_)
{
    other.sockfd_ = -1;
}
SafeSocket& SafeSocket::operator=(SafeSocket&& other){

    if (this != &other) {
        this->close();                 // release current socket
        sockfd_ = other.sockfd_; // steal
        other.sockfd_ = -1;
    }
    return *this;
}

bool SafeSocket::connect(const std::string& path) {
    if (sockfd_ == -1) return false;

    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;

    if (path.size() >= sizeof(addr.sun_path)) {
        return false;
    }

    strncpy(addr.sun_path, path.c_str(), sizeof(addr.sun_path) - 1);

    return (::connect(sockfd_,
                      reinterpret_cast<sockaddr*>(&addr),
                      sizeof(addr)) == 0);
}

ssize_t SafeSocket::read(void* buffer, size_t size) {
    if (sockfd_ == -1) return -1;
    return ::read(sockfd_, buffer, size);
}

bool SafeSocket::writeAll(const void* buffer, size_t size) {
    if (sockfd_ == -1) return false;

    const char* ptr = static_cast<const char*>(buffer);
    size_t remaining = size;

    while (remaining > 0) {
        ssize_t written = ::write(sockfd_, ptr, remaining);

        if (written < 0) {
            if (errno == EINTR) continue;
            return false;
        }

        remaining -= written;
        ptr += written;
    }

    return true;
}


bool SafeSocket::write(const std::string& data) {
    return writeAll(data.c_str(),data.size());
}
bool SafeSocket::write(const void* buffer, size_t size)
{
    return writeAll(buffer,size);
}

bool SafeSocket::isOpen() const {
    return sockfd_ >= 0;
}
