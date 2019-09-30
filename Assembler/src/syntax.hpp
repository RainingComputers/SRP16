#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <string>
#include <algorithm>
#include <cctype>

namespace syntax
{
    bool tokenize(std::string&, std::string&, std::string&, std::string&, int&);
    bool check_line(const std::string&);
    int get_reg_id(const std::string&);
}

#endif