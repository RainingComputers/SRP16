#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <iostream>

namespace log
{
    void syntax_error(const std::string& error, int line_no, 
        std::string&file_name);
    void operand_error(const std::string& error, int line_no,
        std::string&file_name);
    void error(const std::string& error);
    void usage_error(const std::string& error);
    void include_error(const std::string& inc_file_name, int line_no, 
        std::string& file_name);
}


#endif