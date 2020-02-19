#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <string>
#include <algorithm>
#include <cctype>

namespace syntax
{
    bool tokenize(std::string&, std::string&, std::string*, int, int&);
    int get_reg_id(const std::string& operand, int reg_range);
    bool immediate_to_int(const std::string& operand, int& num);
    bool check_range_int(int num, int bits);
}

#endif