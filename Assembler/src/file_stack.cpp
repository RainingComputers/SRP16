#include "file_stack.hpp"

namespace file_stack
{
    file_tracker::file_tracker(const std::string& file_name)
    {
        name = file_name;
        file_stream.open(file_name);
        line_no = 0;
    }

    bool push_file(const std::string& file_name, std::vector<file_tracker>& file_stack)
    {
        /* Push to stack */
        file_stack.emplace_back(file_name);

        /* Check if opened successfully */
        if(!file_stack.back().file_stream.is_open()) 
        {
            file_stack.pop_back();
            return false;
        }

        return true;
    }

    bool pop_file(std::vector<file_tracker>& file_stack)
    {
        file_stack.back().file_stream.close();
        file_stack.pop_back();
        if(file_stack.size() == 0) return false;
        return true;
    }
}