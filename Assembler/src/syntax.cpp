#include "syntax.hpp"

namespace syntax
{
    static void str_tolower(std::string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c){ return std::tolower(c); });
    }

    bool tokenize(std::string& line, std::string& instruction, 
        std::string& first_operand, std::string& second_operand,
        int &token_count)
    {
        /* Remove commas and tabs */
        std::replace_if(line.begin(), line.end(), [](char c)->bool{return isspace(c)||c==',';}, ' ');
        /* Extract tokens */
        token_count = 0;
        for(int i=0; i<line.length();)
        {
            if(line[i] == ' ') i++;
            else
            {
                /* Find end of token */
                size_t pos = line.find(' ', i);
                /* Extract token from line */
                std::string token = line.substr(i, pos-i);
                /* Count */
                token_count++;
                /* Assign token */
                if(token_count == 1) instruction = token;
                else if(token_count == 2) first_operand = token;
                else if(token_count == 3) second_operand = token;
                else
                {
                    return false;
                }
                /* Update i */
                i = pos;
            }
        }

        /* Change all tokens to lower case */
        str_tolower(instruction);
        str_tolower(first_operand);
        str_tolower(second_operand);

        return true;
    }

    bool check_line(const std::string& line)
    {
        /* Count number of commas */
        int comma_count = std::count(line.begin(),line.end(), ',');
        if(comma_count > 2) return false;

        /* Find position of first space, first comma and second comma */
        size_t first_space_pos = line.find(' ');
        size_t first_comma_pos = line.find(',');
        size_t second_comma_pos;
        if(first_comma_pos != std::string::npos)
            second_comma_pos = line.find(',', first_comma_pos+1);
        else
            second_comma_pos = std::string::npos;

        /* Check syntax */
        if(first_comma_pos == std::string::npos)
            return true;
        else
        {
            if((int)(first_comma_pos-first_space_pos) < 2) return false;
            if(second_comma_pos != std::string::npos)
                if((second_comma_pos-first_comma_pos) < 2) return false;

            return true;
        }
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