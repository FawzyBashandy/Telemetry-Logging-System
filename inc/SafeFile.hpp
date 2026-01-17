#pragma once
#include <iostream>

class SafeFile final
{
    private:
    int fd_{-1};
    public:
    explicit SafeFile(const std::string& filePath);
    //Non-Copyable
    SafeFile(const SafeFile&) = delete;
    SafeFile& operator=(const SafeFile&)=delete;
    //Moveable
    SafeFile(SafeFile&&);
    SafeFile& operator=(SafeFile&&);

    //APIs
    void write(const std::string& message);
    ~SafeFile();
};