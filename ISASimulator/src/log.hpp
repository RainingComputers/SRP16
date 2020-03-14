#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <iostream>
#include <iomanip>

/* Converts any int data type to hex string */
template <typename T>
std::string hexstr(T i)
{
    std::stringstream stream;
    stream << "0x" 
        << std::setfill ('0') << std::setw(sizeof(T)*2) 
        << std::hex << (uint)i;
    return stream.str();
}

namespace log
{
    void print(const std::string& error)
    {
        std::cout << error << "\n";
    }

    template <typename T>
    void print_symbol(T i, const std::string& symbol_name, int suffix = -1)
    {
        if(suffix == -1)
            std::cout << symbol_name << " = " << hexstr<T>(i) << "\n";
        else
            std::cout << symbol_name << suffix << " = " << hexstr<T>(i) << "\n";
    }
}


#endif