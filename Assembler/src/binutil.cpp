#include "binutil.hpp"

namespace binutil
{
    std::string byte_to_string(int byte_num, bool newline)
    {
        std::string instr_str;
        
        /* Construct hex string from int */
        for(int i : {1, 0})
        { 
            /* Get ith 4 bits from int */
            unsigned char digit = (byte_num >> (i*4)) & 0x000F;
            /* Convert to valid char */
            if(digit <= 9) digit += 48;
            else digit += 55;
            /* Add to string  */
            instr_str.push_back(digit);
        }

        /* Add new line */
        if(newline) instr_str.push_back('\n');

        return instr_str;
    }

    std::string word_to_string(uint16_t word_int, bool split, bool little)
    {
        std::string instr_str;

        /* Select digit order */
        int little_endian[4] = {1, 0, 3, 2};
        int big_endian[4] = {3, 2, 1, 0};
        int* digit_order;

        if(little) digit_order = little_endian;
        else digit_order = big_endian;

        /* Construct hex string from int */
        for(int i=0; i<4; i++)
        {
            int digit_idx = digit_order[i];
            /* Get ith 4 bits from int */
            unsigned char digit = (word_int >> (digit_idx*4)) & 0x000F;
            /* Convert to valid char */
            if(digit <= 9) digit += 48;
            else digit += 55;
            /* Add to string  */
            instr_str.push_back(digit);
            /* New line after a byte and the end */
            if((digit_idx==0||digit_idx==2)&&split) instr_str.push_back('\n');
        }

        return instr_str;
    }

    void org(std::ofstream& output_file, int size, option_type mode)
    {
        if(mode == VERILOG_HEX || mode == HEX_DEBUG_SYMBOLS)
        {
            for(int i = 0; i < size; i++)
                output_file << "00\n";
        }
    }

    std::string calc_ihex_checksum(uint8_t byte_count, uint16_t address, 
        uint8_t type, uint16_t word)
    {
        int sum = byte_count + (address & 0x00ff) + ((address & 0xff00)>>8)
            + type + (word & 0x00ff) + ((word & 0xff00)>>8);
    
        return byte_to_string(-1*sum);
    }

    void write_word(std::ofstream& output_file, uint16_t word, int address, option_type mode)
    {
        if(mode == INTEL_HEX)
        {
            /* Construct parts of intel hex file record */
            std::string ihex_start = ":";
            std::string ihex_bytes = "02";
            std::string ihex_addr = word_to_string(address, false, false);
            std::string ihex_type = "00";
            std::string ihex_data = word_to_string(word, false);

            std::string ihex_checksum = calc_ihex_checksum(2, address, 0, word);

            /* Write the entire record to output file */
            output_file << ihex_start+ihex_bytes+ihex_addr+ihex_type+ihex_data+ihex_checksum; 
        }
        else if(mode == VERILOG_HEX || mode == HEX_DEBUG_SYMBOLS)
        {
            std::string instr_word_str = word_to_string(word);
            output_file << instr_word_str;
        }
    }

    void write_byte(std::ofstream& output_file, int byte, int address, option_type mode)
    {
        if(mode == INTEL_HEX)
        {
            /* Construct parts of intel hex file record */
            std::string ihex_start = ":";
            std::string ihex_bytes = "01";
            std::string ihex_addr = word_to_string(address, false, false);
            std::string ihex_type = "00";
            std::string ihex_data = byte_to_string(byte, false);

            std::string ihex_checksum = calc_ihex_checksum(1, address, 0, byte);

            /* Write the entire record to output file */
            output_file << ihex_start+ihex_bytes+ihex_addr+ihex_type+ihex_data+ihex_checksum; 
        }
        else if(mode == VERILOG_HEX || mode == HEX_DEBUG_SYMBOLS)
        {
            std::string instr_word_str = byte_to_string(byte);
            output_file << instr_word_str;
        }
    }

    void write_hex_string(std::ofstream& output_file, const std::string& hex_string,
        int address, option_type mode)
    {
        if(mode == INTEL_HEX)
        {
            /* Construct intel hex record */
            std::string ihex_start = ":";
            std::string ihex_bytes = byte_to_string(hex_string.length()/2, false);
            std::string ihex_addr = word_to_string(address, false, false);
            std::string ihex_type = "00";
            std::string ihex_data = hex_string;

            /* Calculate checksum */
            int checksum = (hex_string.length()/2)+(address & 0x00ff)+((address & 0xff00)>>8);
            for(int i=0; i<hex_string.length(); i+=2)
            {
                /* Write to file */
                std::string hex_byte = hex_string.substr(i, 2); 
                checksum += std::stoi(hex_byte, 0, 16);
            }       
            std::string ihex_checksum = byte_to_string(-1*checksum);

            /* Write the entire record to output file */
            output_file << ihex_start+ihex_bytes+ihex_addr+ihex_type+ihex_data+ihex_checksum; 

        }
        else if(mode == VERILOG_HEX || mode == HEX_DEBUG_SYMBOLS)
        {
            for(int i=0; i<hex_string.length(); i+=2)
            {
                /* Write to file */
                output_file<<hex_string[i];
                output_file<<hex_string[i+1];
                output_file<<"\n";
            }
        }
    }

    void write_string(std::ofstream& output_file, const std::string& string_data,
        int address, option_type mode)
    {
        if(mode == INTEL_HEX)
        {
            /* Construct intel hex record */
            std::string ihex_start = ":";
            std::string ihex_bytes = byte_to_string(string_data.length(), false);
            std::string ihex_addr = word_to_string(address, false, false);
            std::string ihex_type = "00";
            
            std::string ihex_data = "";
            for(char c: string_data)
                ihex_data += byte_to_string(c, false);

            /* Calculate checksum */
            int checksum = string_data.length()+(address & 0x00ff)+((address & 0xff00)>>8);
            for(char c : string_data)
                checksum += c;
            std::string ihex_checksum = byte_to_string(-1*checksum);
            
            /* Write the entire record to output file */
            output_file << ihex_start+ihex_bytes+ihex_addr+ihex_type+ihex_data+ihex_checksum; 
            
        }
        else if(mode == VERILOG_HEX || mode == HEX_DEBUG_SYMBOLS)
        {
            for(char c : string_data)
                write_byte(output_file, c, address, mode);
        }
    }

    void write_ihex_eof(std::ofstream& output_file)
    {
        output_file << ":00000001FF";
    }

    /* Functions to help insert debug symbols in binary */
    namespace dbgsym
    {
        void line(std::ofstream& output_file, const std::string& file_name, int line_no)
        {
            output_file<<".line "<<line_no<<" "<<file_name<<"\n";
        }

        void label(std::ofstream& output_file, const std::string& file_name, int line_no, 
            const std::string& label)
        {
            output_file<<".label "<<line_no<<" "<<file_name<<" "<<label<<"\n";
        }
    }

}

