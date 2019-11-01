#include "log.hpp"

namespace log
{
    static void in_file(const std::string& file_name)
    {
        std::cout<<"In file \""<<file_name<<"\":\n";
    }

    void syntax_error(const std::string& error, int line_no, 
        const std::string&file_name)
    {
        in_file(file_name);
        std::cout<<"SYNTAX-ERROR: At line "<<line_no<<", "<<error<<"\n";
    }

    void operand_error(const std::string& error, int line_no,
        const std::string&file_name)
    {
        in_file(file_name);
        std::cout<<"OPERAND-ERROR: At line "<<line_no<<", "<<error<<"\n";
    }

    void error(const std::string& error)
    {
        std::cout<<"ERROR: "<<error<<"\n";
    }

    void usage_error(const std::string& error)
    {
        std::cout<<"USAGE: "<<error<<"\n";
    }

    void include_error(const std::string& inc_file_name, int line_no, 
        const std::string& file_name)
    {
        in_file(file_name);
        std::cout<<"INCLUDE: Unable to open file \""<<inc_file_name<<"\""<<"\n";
    }
}