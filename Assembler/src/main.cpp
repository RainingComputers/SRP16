#include <fstream>
#include <string>

#include "syntax.hpp"
#include "isa.hpp"
#include "log.hpp"

int main(int argc, char *argv[])
{
    /* Check for correct usage */
    if(argc != 3)
    {
        log::usage_error("srp16asm INPUTFILE OUTPUTFILE");
        return EXIT_FAILURE;
    }

    /* Input assembly file */
    std::ifstream input_file(argv[1]);
    if(!input_file.is_open())
    {
        log::error("Unable to open input file");
        return EXIT_FAILURE;
    }

    /* Output .hex file */
    std::ofstream output_file(argv[2]);
    if(!output_file.is_open())
    {
        log::error("Unable to open output file");
        return EXIT_FAILURE;
    }

    /* Process assembly file */
    std::string line;
    int line_no = 0;
    while(std::getline(input_file, line))
    {
        /* Count lines */
        line_no++;

        /* Keep track of address */
        int address = 0;

        /* Ignore everything after semicolon */
        size_t semicolon_pos = line.find(';');
        line = line.substr(0, semicolon_pos);

        /* Tokens */
        std::string instruction = "";
        std::string first_operand = "";
        std::string second_operand = "";
        int token_count = 0;

        /* Syntax check the line */
        if(!syntax::check_line(line))
        {
            log::syntax_error("", line_no);
            return EXIT_FAILURE;            
        }

        /* Tokenize the line */
        if(!syntax::tokenize(line, instruction, first_operand, second_operand, 
            token_count))
        {
            log::syntax_error("", line_no);
            return EXIT_FAILURE;
        }

        /* Process instruction to binary */
        if(instruction == "notf")
        {
            if(token_count>1)
            {
                log::syntax_error("Too many operands", line_no);
                return EXIT_FAILURE;
            }

            uint16_t inst_bin = isa::pack_rtype(0b1100, 0b010000, 0);            
            output_file << isa::instruction_to_str(inst_bin);
        }
        else if(instruction == "mov")
        {
            /* Get register id from operands */
            int register1_id = syntax::get_reg_id(first_operand);
            int register2_id = syntax::get_reg_id(second_operand);

            /* If invalid register id */
            if(register1_id<0 || register2_id<0)
            {
                log::syntax_error("Invalid register", line_no);
                return EXIT_FAILURE;
            }

            /* Build instruction */
            uint16_t inst_bin = isa::pack_rtype(0b1001, register1_id, register2_id);
            output_file << isa::instruction_to_str(inst_bin);
        }
        else if(instruction == "ldr")
        {
            /* Get register id from first operand */
            int register1_id = syntax::get_reg_id(first_operand);

            /* If invalid register id */
            if(register1_id<0)
            {
                log::syntax_error("Invalid register", line_no);
                return EXIT_FAILURE;
            }

            /* Get immediate from operand */
            int immediate;
            if(!syntax::immediate_to_int(second_operand, immediate))
            {
                log::syntax_error("Invalid operand", line_no);
                return EXIT_FAILURE;
            }

            /* Build instruction */
            uint16_t inst_bin = isa::pack_etype(0, register1_id, immediate);
            output_file << isa::instruction_to_str(inst_bin);
        }
        else
        {
            log::syntax_error("Unknown instruction or directive", line_no);
            return EXIT_FAILURE;
        }

        /* Count address */
        address += 2;
    }

    /* Close files */
    input_file.close();
    output_file.close();
    
    /* Exit successfully */
    return EXIT_SUCCESS;
}