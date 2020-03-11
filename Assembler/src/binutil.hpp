#ifndef BINUTIL_HPP
#define BINUTIL_HPP

#include <string>
#include <fstream>

namespace binutil
{
    enum option_type {INTEL_HEX, VERILOG_HEX, HEX_DEBUG_SYMBOLS};

    std::string byte_to_string(int byte_num, bool newline=true);
    std::string word_to_string(uint16_t word_int, bool split=true, bool little=true);
    void org(std::ofstream& output_file, int size, option_type mode);
    void write_word(std::ofstream& output_file, uint16_t word, int address, option_type mode);
    void write_byte(std::ofstream& output_file, int byte, int address, option_type mode);
    void write_ihex_eof(std::ofstream& output_file);
    void write_hex_string(std::ofstream& output_file, const std::string& hex_string,
        int address, option_type mode);
    void write_string(std::ofstream& output_file, const std::string& string_data,
        int address, option_type mode);

    namespace dbgsym
    {
        void line(std::ofstream& output_file, const std::string& file_name, int line_no);
        void label(std::ofstream& output_file, const std::string& file_name, int line_no, 
            const std::string& label);
    }
}

#endif