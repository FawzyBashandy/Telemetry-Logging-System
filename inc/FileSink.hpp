#pragma once
#include <ILogSink.hpp>
#include <SafeFile.hpp>
class FileSink final : public ILogSink
{
    private:
    SafeFile _sinkFile;
    public:
    explicit FileSink(const std::string &filePath);

    //Non-Copyable
    /*optional as : 
    this will be done automatically by compiler since member SafeFile is non-copyable*/
    FileSink(const FileSink & other) = delete; 
    FileSink & operator=(const FileSink & other) = delete;
    //Moveable
    FileSink(FileSink && other) = default;
    FileSink & operator=(FileSink && other) = default;
    
    void write(const std::string& message) override;

    ~FileSink()override = default;
};
