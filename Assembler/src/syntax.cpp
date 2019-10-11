#include "syntax.hpp"

namespace syntax
{
    static void str_tolower(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c){ return std::tolower(c); });
    }

    bool tokenize(std::string& line, std::string& instruction, 
        std::string operands[], int max_tokens, 
        int &token_count)
    {
        /* Remove commas and tabs */
        std::replace_if(line.begin(), line.end(), 
            [](char c)->bool{return isspace(c);}, ' ');
        /* Add space at the end to ensure last token is processed */
        line+=' ';
        /* Extract tokens */
        token_count = 0;
        int start_pos = 0;
        int end_pos = 0;
        bool token_start = false;
        bool expecting_comma = false;
        for(int i=0; i<line.length(); i++)
        {
            if(line[i] == ' ' || line[i] == ',')
            {
                /* Extract token if found */
                if(token_start)
                {
                    token_count++;
                    std::string token = line.substr(start_pos, i-start_pos);
                    if(token_count == 1) instruction = token;
                    else if(token_count <= max_tokens)
                    {
                        operands[token_count-2] = token;
                        expecting_comma = true;
                    }
                    else return false;
                    /* Token found */
                    token_start = false;
                }
                /* Check for commas */
                if(line[i] == ',')
                    if(!expecting_comma) return false;
                    else expecting_comma = false;
            }
            else if(!token_start)
            {
                start_pos = i;
                token_start = true;
            }
        }

        /* Change all tokens to lower case */
        str_tolower(instruction);
        for(int i=0; i<token_count-1; i++)
            str_tolower(operands[i]);

        return true;
    }

    int get_reg_id(const std::string& operand, bool general_purpose)
    {
        if(operand[0] == 'r')
        {
            /* Check if valid register id */
            if(operand.length() > 3) return -1;
            else if(operand.length() == 3)
            {
                /* If 'r' is not followed by anumber, invalid */
                if(!isdigit(operand[1]) || !isdigit(operand[2])) 
                    return -1;

                /* Get register id from number */
                int id = (operand[2]-48) + (operand[1]-48)*10;

                /* Check if in range and return */
                if(id < 64 && !general_purpose) return id;
                else if(id < 32) return id;
                else return -1;
            }
            else if(operand.length() == 2)
            {
                /* If 'r' is not followed by anumber, invalid */
                if(!isdigit(operand[1]) ) return -1;

                /* Get id and return it */
                return (operand[1]-48);
            }
        }
        else if(operand == "a") return 60;
        else if(operand == "mptr") return 61;
        else if(operand == "sp") return 62;
        else if(operand == "pc") return 63;
        else return -1;
    }

    bool immediate_to_int(const std::string& operand, int& num)
    {
        /* Syntax check */
        if(operand[0] == '0' && operand[1] == 'x')
        {
            for(int i=2; i<operand.length(); i++)
            {
                char c = operand[i];
                if(!(isdigit(c) || (c>='a' && c<='f'))) return false;
            }
        }
        else
        {
            for(int i=0; i<operand.length(); i++)
                if(i==0 && operand[i]=='-') continue;
                else if(!isdigit(operand[i])) return false;
        }

        /* If syntax check passed, convert to int and return true */
        num = std::stoi(operand, nullptr, 0);
        return true;
    }

    bool check_range_int(int num, int bits, bool usigned=false)
    {
        if(usigned)
        {
            if(num < (1<<bits) && num >= 0) return true;
            else return false;
        }
        else
        {
            /* Get minimum and maximum value that num can take */
            int min = -1* (1<<bits)/2;
            int max = (1<<bits)/2 - 1;
    
            /* Check if within limits */
            if(num >= min && num <= max) return true;
            else return false;
        }
    }
}