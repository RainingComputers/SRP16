#include "log.hpp"

namespace log
{
    void syntax_error(const std::string& error, int line_no)
    {
        std::cout<<"SYNTAX-ERROR: At line "<<line_no<<", "<<error<<"\n";
    }

    void operand_error(const std::string& error, int line_no)
    {
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
}