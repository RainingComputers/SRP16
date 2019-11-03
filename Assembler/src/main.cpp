#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "syntax.hpp"
#include "isa.hpp"
#include "log.hpp"
#include "file_stack.hpp"

#define MAX_TOKENS 3

int main(int argc, char *argv[])
{
    /* Create file stack */
    std::vector<file_stack::file_tracker> fstack;

    /* Map for symbol table */
    std::map<std::string, int> symbol_table;

    /* Check for correct usage */
    if(argc != 3)
    {
        log::usage_error("srp16asm INPUTFILE OUTPUTFILE");
        return EXIT_FAILURE;
    }

    /* Output .hex file */
    std::ofstream output_file(argv[2]);
    if(!output_file.is_open())
    {
        log::error("Unable to open output file");
        return EXIT_FAILURE;
    }

    /* String for holding current line being processed */
    std::string line;

    /*
        ==================================
        = First pass, build symbol table = 
        ==================================
    */

    /* Input assembly file */
    std::string input_file = argv[1];
    if(!file_stack::push_file(input_file, fstack))
    {
        log::error("Unable to open input file");
        return EXIT_FAILURE;
    }

    /* Keep track of address */
    int address = 0;

    /* Process assebmly files to build symbol table */
    while(true)
    {
        /* Get line from current file being processed */
        if(!std::getline(fstack.back().file_stream, line))
        {
            if(!file_stack::pop_file(fstack)) break;
            else continue;
        }

        /* Count lines */
        fstack.back().line_no++;
        int line_no = fstack.back().line_no;

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
            log::syntax_error("", line_no, fstack.back().name);
            return EXIT_FAILURE;
        }

        /* Ignore blank lines */
        if(token_count == 0) continue;

        /* Check for assembler preprocessors */
        if(str_instr.back() == ':')
        {
            /* Token count */
            if(token_count-1 > 0)
            {
                log::operand_error("Invalid number of operands", line_no, 
                    fstack.back().name);
                return EXIT_FAILURE;                
            }
            /* Remove colon */
            str_instr.pop_back();
            /* Check if label already exists */
            if(symbol_table.find(str_instr) != symbol_table.end())
            {
                log::syntax_error("Label already defined", line_no,
                    fstack.back().name);
                return EXIT_FAILURE;
            }
            /* add to table */
            symbol_table[str_instr] = address;
        }
        else if(str_instr == ".equ")
        {
            /* Check if label already exists */
            if(symbol_table.find(str_operands[0]) != symbol_table.end())
            {
                log::syntax_error("Symbol already defined", line_no,
                    fstack.back().name);
                return EXIT_FAILURE;
            }
            /* add to table */
            int value;
            if(!syntax::immediate_to_int(str_operands[1], value))
            {
                log::syntax_error("Invalid operand token", line_no,
                    fstack.back().name);                       
                return EXIT_FAILURE;
            }
            symbol_table[str_operands[0]] = value;
        }
        else if(str_instr == ".org")
        {
            /* Token count */
            if(token_count-1 > 1)
            {
                log::operand_error("Invalid number of operands", line_no, 
                    fstack.back().name);
                return EXIT_FAILURE;                
            }
            /* Get location */
            int location;
            if(!syntax::immediate_to_int(str_operands[0], location))
            {
                log::syntax_error("Invalid operand token", line_no,
                    fstack.back().name);                       
                return EXIT_FAILURE;
            }
            /* No negetive orgs */
            if(location <= address)
            {
                log::syntax_error("Invalid org location", line_no,
                    fstack.back().name);                       
                return EXIT_FAILURE;    
            }
            address = location;
        }
        else if(str_instr == "jmp")
        {
            address+=2;
        }
        else if(str_instr == ".byte")
        {
            /* Token count */
            if(token_count-1 > 1)
            {
                log::operand_error("Invalid number of operands", line_no, 
                    fstack.back().name);
                return EXIT_FAILURE;                
            }
            /* Update address */
            address+=1;
        }
        else if(str_instr == ".string")
        {
            /* Token count */
            if(token_count-1 > 1)
            {
                log::operand_error("Invalid number of operands", line_no, 
                    fstack.back().name);
                return EXIT_FAILURE;                
            }
            /* Updtate address */
            address+=str_operands[0].length();
        }
        else if(str_instr == ".hex")
        {
            /* Token count */
            if(token_count-1 > 1)
            {
                log::operand_error("Invalid number of operands", line_no, 
                    fstack.back().name);
                return EXIT_FAILURE;                
            }
            /* Check if valid hex string */
            for(char c: str_operands[0])
            {
                if(!((c>='0' && c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F')))
                {
                    log::syntax_error("Invalid hex string", line_no, 
                        fstack.back().name);
                    return EXIT_FAILURE; 
                }
            }   
            /* Get length */
            int length = str_operands[0].length();
            /* If not even */
            if(length%2!=0)
            {
                log::syntax_error("Number of digits should be even", line_no,
                    fstack.back().name);
                return EXIT_FAILURE;                
            }
            /* Update address */
            address+=length/2;
        }
        else if(str_instr == ".include")
        {
            /* Token count */
            if(token_count-1 > 1)
            {
                log::operand_error("Invalid number of operands", line_no, 
                    fstack.back().name);
                return EXIT_FAILURE;                
            }
            /* Push new file to the file stack */
            if(!file_stack::push_file(str_operands[0], fstack))
            {
                log::include_error(str_operands[0], line_no,
                    fstack.back().name);
                return EXIT_FAILURE;
            }
        }
        /* if not a preprocessor, then it is a cpu instruction */
        /* Check if it exists */
        else if(isa::instr_properties.find(str_instr) == isa::instr_properties.end())
        {
            log::syntax_error("Unknown instruction or preprocessor", line_no,
                fstack.back().name);
            return EXIT_FAILURE;
        }
        /* If the cpu instruction does exist */
        else
        {
            /* Increment address */
            address+=2;
        }
    }

    /*
        =========================
        = Second pass, assemble = 
        =========================
    */

    /* Input assembly file */
    if(!file_stack::push_file(input_file, fstack))
    {
        log::error("Unable to open input file");
        return EXIT_FAILURE;
    }

    /* Keep track of address */
    address = 0;

    /* Process assembly files to .hex file */
    while(true)
    {
        /* Get line from current file being processed */
        if(!std::getline(fstack.back().file_stream, line))
        {
            if(!file_stack::pop_file(fstack)) break;
            else continue;
        }

        /* Count lines */
        fstack.back().line_no++;
        int line_no = fstack.back().line_no;

        /* Ignore everything after semicolon */
        size_t semicolon_pos = line.find(';');
        line = line.substr(0, semicolon_pos);

        /* Tokens */
        std::string str_instr = "";
        std::string str_operands[2] = {"", ""};
        int token_count = 0;

        /* Tokenize the line to instruction and its operands */
        syntax::tokenize(line, str_instr, str_operands, MAX_TOKENS, 
            token_count);

        /* Ignore blank lines */
        if(token_count == 0) continue;

        /* Check for assembler preprocessors */
        if(str_instr.back() == ':')
            continue;
        else if(str_instr == ".equ")
            continue;
        else if(str_instr == ".org")
        {
            int location;
            syntax::immediate_to_int(str_operands[0], location);
            address = location;
            /* zero till org location is reached */
            for(int i=1; i<address-1; i++)
            {
                output_file<<"00\n";
            }
        }
        else if(str_instr == ".byte")
        {
            int byte_num;
            /* Convert str operand to int */
            if(!syntax::immediate_to_int(str_operands[0], byte_num))
            {
                log::syntax_error("Invalid operand token", line_no,
                    fstack.back().name);                       
                return EXIT_FAILURE;
            }
            /* Check if immediate value is within range */
            if(!syntax::check_range_int(byte_num, 8))
            {
                log::operand_error("Value out of range", line_no, 
                    fstack.back().name);
                return EXIT_FAILURE;    
            }
            /* Write to file */
            address+=1;
            output_file<<syntax::byte_to_string(byte_num);
        }
        else if(str_instr == ".string")
        {
            for(char c : str_operands[0])
            {
                /* Write to file */
                address+=1;
                output_file<<syntax::byte_to_string(c);
            }
        }
        else if(str_instr == ".hex")
        {         
            /* Write to file */
            for(int i=0; i<str_operands[0].length(); i+=2)
            {
                /* Write to file */
                output_file<<str_operands[0][i];
                output_file<<str_operands[0][i+1];
                output_file<<"\n";
                address+=1;
            }
        }
        else if(str_instr == ".include")
        {
            /* Push new file to the file stack */
            if(!file_stack::push_file(str_operands[0], fstack))
            {
                log::include_error(str_operands[0], line_no,
                    fstack.back().name);
                return EXIT_FAILURE;
            }
        }
        /* if not a preprocessor, then it is a cpu instruction */
        else
        {
            /* Check for pseudo instructions */
            if(str_instr == "jmp")
            {
                /* Change JMP Ry to MOV PC, Ry */
                str_instr == "mov";
                str_operands[1] = str_operands[0];
                str_operands[0] = "pc";
            }

            /* Get instruction properties and formats */
            isa::property instr_property = isa::instr_properties[str_instr];
            isa::format instr_format = isa::instr_formats[instr_property.instr_type];

            /* Check if there are correct number of operands */
            if(token_count-1 != instr_format.no_operands)
            {
                log::operand_error("Invalid number of operands", line_no, 
                    fstack.back().name);
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
                    case isa::LREGISTER:
                        int reg_range;
                        switch(instr_format.operand_type[i])
                        {
                            case isa::REGISTER:
                                reg_range = 63;
                                break;
                            case isa::GPREGISTER:
                                reg_range = 31;
                                break;
                            case isa::LREGISTER:
                                reg_range = 15;
                                break;
                        }
                        /* Get regid and check if valid */
                        regid[i] = syntax::get_reg_id(str_operands[i], reg_range);
                        if(regid[i] < 0)
                        {
                            log::operand_error("Invalid register", line_no,
                                fstack.back().name);
                            return EXIT_FAILURE;
                        }
                        break;
                    case isa::RIMMEDIATE:
                    case isa::IMMEDIATE:
                        /* Check symbol table */
                        if(symbol_table.find(str_operands[i]) != symbol_table.end())
                        {
                            immediate = symbol_table[str_operands[i]];
                            /* If relative */
                            if(instr_format.operand_type[i] == isa::RIMMEDIATE)
                                immediate -= address;
                        }
                        /* If not in table Convert str operand to int */
                        else if(!syntax::immediate_to_int(str_operands[i], immediate))
                        {
                            log::syntax_error("Invalid immediate token", line_no,
                                fstack.back().name);                       
                            return EXIT_FAILURE;
                        }

                        /* Check if immediate value is within range */
                        if(!syntax::check_range_int(immediate, instr_format.immediate_size))
                        {
                            log::operand_error("Immediate value out of range", line_no,
                                fstack.back().name);
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
    }

    /* Close files */
    output_file.close();
    
    /* Exit successfully */
    return EXIT_SUCCESS;
}