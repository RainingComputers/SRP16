#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <iostream>

namespace log
{
    void syntax_error(const std::string& error, int line_no);
    void error(const std::string& error);
    void usage_error(const std::string& error);
}


#endif