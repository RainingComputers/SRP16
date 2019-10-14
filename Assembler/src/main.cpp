#include <fstream>
#include <string>

#include "syntax.hpp"
#include "isa.hpp"
#include "log.hpp"

#define MAX_TOKENS 3

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
        std::string str_instr = "";
        std::string str_operands[2] = {"", ""};
        int token_count = 0;

        /* Tokenize the line to instruction and its operands */
        if(!syntax::tokenize(line, str_instr, str_operands, MAX_TOKENS, 
            token_count))
        {
            log::syntax_error("", line_no);
            return EXIT_FAILURE;
        }

        /* Check for assembler preprocessors */
        if(str_instr == "jmp")
        {
            /* Change JMP Ry to MOV PC, Ry */
            str_instr == "mov";
            str_operands[1] = str_operands[0];
            str_operands[0] = "pc";
        }
        else if(str_instr == ".byte")
        {
            if(token_count-1 > 1)
            {
                log::operand_error("Invalid number of operands", line_no);
                return EXIT_FAILURE;                
            }
            int byte_num;
            /* Convert str operand to int */
            if(!syntax::immediate_to_int(str_operands[0], byte_num))
            {
                log::syntax_error("Invalid immediate token", line_no);                       
                return EXIT_FAILURE;
            }
            /* Check if immediate value is within range */
            if(!syntax::check_range_int(byte_num, 8, true))
            {
                log::operand_error("Value out of range", line_no);
                return EXIT_FAILURE;    
            }
            /* Write to file */
            address+=1;
            output_file<<syntax::byte_to_string(byte_num);
            continue;
        }

        /* if not a preprocessor, then it is a cpu instruction */
        /* Check if it exists */
        if(isa::instr_properties.find(str_instr) == isa::instr_properties.end())
        {
            log::syntax_error("Unknown instr or preprocessor", line_no);
            return EXIT_FAILURE;
        }

        /* Get instruction properties and formats */
        isa::property instr_property = isa::instr_properties[str_instr];
        isa::format instr_format = isa::instr_formats[instr_property.instr_type];

        /* Check if there are correct number of operands */
        if(token_count-1 != instr_format.no_operands)
        {
            log::operand_error("Invalid number of operands", line_no);
            return EXIT_FAILURE;
        }

        /* Process string operands to register id or immediate integers */
        int immediate, regid[2];
        for(int i=0; i<instr_format.no_operands; i++)
        {
            switch(instr_format.operand_type[i])
            {
                case isa::REGISTER:
                case isa::GPREGISTER:
                    regid[i] = syntax::get_reg_id(str_operands[i], instr_format.operand_type[i]);
                    if(regid[i] < 0)
                    {
                        log::operand_error("Invalid register", line_no);
                        return EXIT_FAILURE;
                    }
                    break;
                case isa::IMMEDIATE:
                    /* Convert str operand to int */
                    if(!syntax::immediate_to_int(str_operands[i], immediate))
                    {
                        log::syntax_error("Invalid immediate token", line_no);                       
                        return EXIT_FAILURE;
                    }

                    /* Check if immediate value is within range */
                    if(!syntax::check_range_int(immediate, instr_format.immediate_size, 
                        instr_property.immediate_type))
                    {
                        log::operand_error("Immediate value out of range", line_no);
                        return EXIT_FAILURE;    
                    }
                    break;
            }
        }

        /* Create binary instruction word */
        uint16_t instr_word;
        switch(instr_property.instr_type)
        {
            case isa::E_TYPE_LOAD:
                instr_word = isa::pack_etype(
                    instr_property.opcode1, regid[0], immediate
                );
                break;
            case isa::T_TYPE_LOAD:
                instr_word = isa::pack_ttype(
                    instr_property.opcode1, immediate
                );
                break;
            case isa::R_TYPE_LOAD:
            case isa::R_TYPE_IMM_ARITH:
                instr_word = isa::pack_rtype(
                    instr_property.opcode1, instr_property.opcode2, immediate
                );
                break;
            case isa::R_TYPE_MOV:
                instr_word = isa::pack_rtype(
                    instr_property.opcode1, regid[0], regid[1]
                );
                break;
            case isa::T_TYPE_JUMP:
                instr_word = isa::pack_ttype(
                    instr_property.opcode1, immediate
                );
                break;
            case isa::R_TYPE_STACK:
            case isa::R_TYPE_INCDEC:
            case isa::R_TYPE_ARITH:
            case isa::R_TYPE_CMP:
                instr_word = isa::pack_rtype(
                    instr_property.opcode1, instr_property.opcode2, regid[1]
                );
                break;
            case isa::E_TYPE_IMM_ARITH:
            case isa::E_TYPE_CMP_IMM:
                instr_word = isa::pack_etype(
                    instr_property.opcode1, instr_property.opcode2, immediate
                );
                break;
            case isa::R_TYPE_FLAG:
                instr_word = isa::pack_rtype(
                    instr_property.opcode1, instr_property.opcode2, instr_property.opcode3
                );
                break;

        }

        /* Write instruction word to file */
        std::string instr_word_str = syntax::word_to_string(instr_word);
        output_file << instr_word_str;
        
        /* Increment address */
        address+=2;
    }

    /* Close files */
    input_file.close();
    output_file.close();
    
    /* Exit successfully */
    return EXIT_SUCCESS;
}