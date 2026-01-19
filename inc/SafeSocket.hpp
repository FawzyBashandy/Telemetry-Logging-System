#pragma once
#include <iostream>

class SafeSocket final {
public:
    SafeSocket();
    ~SafeSocket();

    // Non-copyable
    SafeSocket(const SafeSocket&) = delete;
    SafeSocket& operator=(const SafeSocket&) = delete;

    // Movable
    SafeSocket(SafeSocket&& other) noexcept;
    SafeSocket& operator=(SafeSocket&& other) noexcept;

    bool connect(const std::string& path);

    ssize_t read(void* buffer, size_t size);
    bool write(const void* buffer, size_t size);
    bool write(const std::string& data);


    bool isOpen() const;

private:
    int sockfd_{-1};

    void close();
    bool writeAll(const void* buffer, size_t size);

};
