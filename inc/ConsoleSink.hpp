#pragma once
#include <ILogSink.hpp>
class ConsoleSink final : public ILogSink{
    public:

    enum class Stream
    {
        StdOut,
        StdErr
    };

    explicit ConsoleSink(Stream s = Stream::StdOut);
    
    void write(const std::string& message)override;

    ConsoleSink(const ConsoleSink& other) =default;
    ConsoleSink(ConsoleSink&& other)=default;
    
    ConsoleSink& operator=(const ConsoleSink& other)=default;
    ConsoleSink& operator=(ConsoleSink& other)=default;

    ~ConsoleSink()override =default;

    private:
    Stream stream_;

};