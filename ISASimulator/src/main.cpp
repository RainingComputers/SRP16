/*
    SRP16 ISA Simulator
*/

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <regex>
#include <list>

#include <readline/readline.h>
#include <readline/history.h>

#include "cpu.hpp"
#include "log.hpp"
#include "split.hpp"
#include "unilist.hpp"

void print_usage()
{
    log::print("USAGE: srp16sim DHEXFILE");  
}

int main(int argc, char *argv[])
{
    /* Check for correct usage */
    if(argc != 2)
    {
        print_usage();
        return EXIT_FAILURE;
    }

    /* New cpu object */
    cpu::srp16cpu vcpu;

    /* Symbol table for labels */
    std::map<std::string, int> symbol_table;

    /* Table for storing address and the corresponding line no */
    std::map<int, std::pair<int, std::string>> addr_line_table;

    /* Vector for storing breakpoints */
    unilist<std::pair<int, std::string>> breakpoints;

    /* Open input file */    
    std::ifstream input_file(argv[1]);

    /* Load program into memory and build symbol-table */
    std::string line;
    int address_count = 0;

    /* Regular expressions for debug symbols */
    std::regex line_dbgsym(R"(\.line\s\d+\s".+")");
    std::regex label_dbgsym(R"(\.label\s\d+\s".+"\s\w+)");

    while(std::getline(input_file, line))
    {
        std::vector<std::string> tokens;
        
        /* Check for debug symbols */
        if(std::regex_match(line, line_dbgsym))
        {
            /* .line debug symbol */
            split(line, tokens);

            /* Add the line number, file name and the address to the table */
            int line_no = std::stoi(tokens[1]);
            std::string file_name = tokens[2];
            addr_line_table[address_count] = 
                std::pair<int, std::string>(line_no, file_name);

        }
        else if(std::regex_match(line, label_dbgsym))
        {
            /* .label debug symbol */
            split(line, tokens);

            /* Add the label and the address to symbol table */
            std::string label_name = tokens[3];
            symbol_table[label_name] = address_count;
        }
        else
        {
        
            /* 
                If it is not a valid symbol, it most be a byte, 
                try to load it into memory
            */
            try
            {
                vcpu.memory[address_count] = std::stoi(line, 0, 16);
                address_count+=1;
            }
            catch(std::invalid_argument)
            {
                log::print("Unknown debug symbol or currupt dhex file");
                return EXIT_FAILURE;
            }
        }
    }

    /* Regular expressions for some commands */
    std::regex mem_regex(R"(mem((\[[0-9A-Fa-fx]+:[0-9A-Fa-fx]+\])|(\[[0-9A-Fa-fx]+\])))");
    std::regex id_regex(R"(r\d+)");
    std::regex bp_regex(R"(bp\s".+"\s\d+)");
    std::regex rmbp_regex(R"(rmbp\s".+"\s\d+)");

    /* For storing current line number */
    int line_no = -1;
    std::string file_name = "NA";

    auto update_line_no = [&]()
    {
        /* Update line number */
        uint16_t pc = vcpu.registers[cpu::PC];
        if(addr_line_table.find(pc) != addr_line_table.end())
        {
            line_no = addr_line_table[pc].first;
            file_name = addr_line_table[pc].second;
        }
    };

    update_line_no();

    /* Start simulation */
    while(true)
    {
        /* Interactive command prompt */
        std::string prompt = 
            "(pc@"+hexstr(vcpu.registers[cpu::PC])+") ";
        
        /* Get input command for input */
        rl_ignore_completion_duplicates = 1;
        char* input = readline(prompt.c_str());
        std::string command(input);

        /* Add command to history, avoid duplicaates */
        HIST_ENTRY* history = previous_history();
        if(history == NULL)
            add_history(input);
        else if(strcmp(history->line, input) != 0)
            add_history(input);

        /* Check for EOF */
        if(!input) break;

        /* Simulator commands */
        if(command == "step")
        {
            /* Step cpu by one instruction */
            vcpu.step();
            update_line_no();
        }
        else if(command == "run")
        {
            while(true)
            {
                /* Step */
                vcpu.step();
                /* Update line no */
                update_line_no();
                /* Check for breakpoint */
                std::pair<int, std::string> point(line_no, file_name);
                if(breakpoints.find(point) != breakpoints.size())
                    break;
            }
        }
        else if(command == "reg")
        {
            /* Print all registers in the CPU */

            log::print_symbol<uint16_t>(vcpu.instruction_reg, "ir");
            log::print_symbol<uint16_t>(vcpu.registers[cpu::PC], "pc");
            log::print_symbol<uint16_t>(vcpu.registers[cpu::A], "a");
            log::print_symbol<uint16_t>(vcpu.registers[cpu::MPTR], "mptr");
            log::print_symbol<uint16_t>(vcpu.registers[cpu::SP], "sp");
            log::print_symbol<uint16_t>(vcpu.carry, "carry");
            log::print_symbol<uint16_t>(vcpu.flag, "flag");

            for(int i = 0; i < 32; i++)
            {
                log::print_symbol<uint16_t>(vcpu.registers[i], "r", i);
            }
        }
        else if(command == "ir")
        {
            log::print_symbol<uint16_t>(vcpu.instruction_reg, "ir");
        }
        else if(command == "pc")
        {
            log::print_symbol<uint16_t>(vcpu.registers[cpu::PC], "pc");           
        }
        else if(command == "a")
        {
            log::print_symbol<uint16_t>(vcpu.registers[cpu::A], "a");           
        }
        else if(command == "mptr")
        {
            log::print_symbol<uint16_t>(vcpu.registers[cpu::MPTR], "mptr");           
        }
        else if(command == "sp")
        {
            log::print_symbol<uint16_t>(vcpu.registers[cpu::SP], "sp");          
        }
        else if(command == "carry")
        {
            log::print_symbol<uint16_t>(vcpu.carry, "carry");          
        }
        else if(command == "flag")
        {
            log::print_symbol<uint16_t>(vcpu.flag, "flag");          
        }
        else if(command == "line")
        {
            log::line(line_no, file_name);
        }
        else if(std::regex_match(command, id_regex))
        {
            int reg_id = std::stoi(command.substr(1));
            
            if(reg_id > 63 || reg_id < 0)
            {
                log::print("Invalid register");
                continue;
            }

            log::print_symbol<uint16_t>(vcpu.registers[reg_id], "r", reg_id);
        }
        else if(std::regex_match(command, mem_regex))
        {
            int start, end;

            /* Parse command and get start and end address */
            int colon_pos = command.find(":");
            if(colon_pos == std::string::npos)
            {
                /* For only one single address */
                start = std::stoi(command.substr(4, command.length()-5), 0, 16);
                end = start+1;
            }
            else
            {
                /* For range of addresses */
                start = std::stoi(command.substr(4, colon_pos-4), 0, 16);
                end = std::stoi(command.substr(colon_pos+1, 
                    command.length()-colon_pos), 0, 16);
            }

            /* Print that section of memory */
            for(uint16_t i = start; i < end; i++)
            {
                std::cout << "mem[" << hexstr<uint16_t>(i) << "] = ";
                std::cout << hexstr<uint8_t>(vcpu.memory[i]) << std::endl;
            }
            
        }
        else if(std::regex_match(command, bp_regex))
        {
            std::vector<std::string> tokens;
            split(command, tokens);

            std::string file_name = tokens[1];
            int line_no = std::stoi(tokens[2]);

            breakpoints.add(std::pair<int, std::string>(line_no, file_name));
        }
        else if(std::regex_match(command, rmbp_regex))
        {
            std::vector<std::string> tokens;
            split(command, tokens);

            std::string file_name = tokens[1];
            int line_no = std::stoi(tokens[2]);

            breakpoints.remove(std::pair<int, std::string>(line_no, file_name));
        }
        else if(command == "exit")
        {
            return EXIT_SUCCESS;
        }
        else if(symbol_table.find(command) != symbol_table.end())
        {
            log::print_symbol<uint16_t>(symbol_table[command], command);
        }
        else
        {
            log::print("Unknown command or symbol name");
        }
        
        /* Free buffer that was allocated by readline */
        free(input);

    }
}