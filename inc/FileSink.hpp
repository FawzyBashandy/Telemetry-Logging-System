#pragma once
#include <ILogSink.hpp>
class FileSink final : public ILogSink
{
    private:
    int fd_{-1};
    public:
    explicit FileSink(const std::string &filePath);

    //Non-Copyable
    FileSink(const FileSink & other) = delete;
    FileSink & operator=(const FileSink & other) = delete;
    //Moveable
    FileSink(FileSink && other);
    FileSink & operator=(FileSink && other);
    
    void write(const std::string& message) override;

    ~FileSink() override;
};
