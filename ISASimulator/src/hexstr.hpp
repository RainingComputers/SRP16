#ifndef HEXSTR_HPP
#define HEXSTR_HPP

#include <string>
#include <sstream>
#include <iomanip>

template <typename T>
std::string int_to_hex( T i )
{
    std::stringstream stream;
    stream << "0x" 
        << std::setfill ('0') << std::setw(sizeof(T)*2) 
        << std::hex << i;
    return stream.str();
}

#endif