#pragma once
#include <iostream>

class SafeFile final
{
    private:
    int fd_{-1};
    void close();
    public:
    SafeFile()=default;
    //Non-Copyable
    SafeFile(const SafeFile&) = delete;
    SafeFile& operator=(const SafeFile&)=delete;
    //Moveable
    SafeFile(SafeFile&&);
    SafeFile& operator=(SafeFile&&);

    //APIs
    bool open(const std::string& filePath);

    bool SafeFile::readLine(std::string& out);

    bool write(const std::string& message);
    ~SafeFile();
};