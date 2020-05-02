#include "split.hpp"

void split(const std::string &txt, std::vector<std::string> &strs)
{   
    /* Clear token lost */
    strs.clear();

    for(int i=0; i<txt.length(); i++)
    {
        if(txt[i] == '"')
        {
            size_t quote_end = txt.find('"', i+1);

            if(quote_end == std::string::npos)
                quote_end = txt.length();
            
            strs.push_back(txt.substr(i+1, quote_end-i-1));
            i = quote_end;
        }
        else if(txt[i] != ' ')
        {
            size_t space_end = txt.find(' ', i+1);

            if(space_end == std::string::npos)
                space_end = txt.length();
            
            strs.push_back(txt.substr(i, space_end-i));
            i = space_end;
        }
    }
}