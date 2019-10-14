#ifndef FILE_STACK_HPP
#define FILE_STACK_HPP

#include <vector>
#include <fstream>
#include <string>

namespace file_stack
{
    /* Stack for processing files */
    /* New file will be pushed with .include preprocessor */
    struct file_tracker
    {
        std::string name;
        std::ifstream file_stream;
        int line_no;

        file_tracker(const std::string& file_name);
    };

    bool push_file(const std::string& file_name, std::vector<file_tracker>& file_stack);
    bool pop_file(std::vector<file_tracker>& file_stack);
}


#endif