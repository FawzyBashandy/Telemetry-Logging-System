#include "ConsoleSink.hpp"
#include <iostream>
ConsoleSink::ConsoleSink(Stream s) : stream_(s)
{

}
    
void ConsoleSink::write(const std::string& message)
{
    std::ostream& os = (stream_ == Stream::StdOut) ? std::cout : std::cerr;

    os << message << "\n";
    os.flush();
}