#ifndef HEXSTR_HPP
#define HEXSTR_HPP

#include <string>
#include <iomanip>

/* Converts any int data type to hex string */
template <typename T>
std::string hexstr( T i )
{
    std::stringstream stream;
    stream << "0x" 
        << std::setfill ('0') << std::setw(sizeof(T)*2) 
        << std::hex << (uint)i;
    return stream.str();
}

#endif