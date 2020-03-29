/*
    SRP16 ISA Simulator
*/

#include <fstream>
#include <string>
#include <regex>

#include "cpu.hpp"
#include "log.hpp"

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

    /* Open input file */    
    std::ifstream input_file(argv[1]);

    /* Load program into memory and build symbol-table */
    std::string line;
    int address_count = 0;
    while(std::getline(input_file, line))
    {
        vcpu.memory[address_count] = std::stoi(line, 0, 16);
        address_count+=1;
    }

    /* Regular expressions for some commands */
    std::regex mem_regex(R"(mem((\[[0-9A-Fa-fx]+:[0-9A-Fa-fx]+\])|(\[[0-9A-Fa-fx]+\])))");
    std::regex id_regex(R"(r\d+)");

    /* Start simulation */
    while(true)
    {
        std::string command;
        
        /* Interactive command prompt */
        std::cout << "(pc@";
        std::cout << hexstr(vcpu.registers[cpu::PC]);
        std::cout << ") ";
        std::cin >> command;

        /* Simulator commands */
        if(command == "step")
        {
            /* Step cpu by one instruction */
            vcpu.step();
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
        else if(command == "exit")
        {
            return EXIT_SUCCESS;
        }
        else
        {
            log::print("Unknown command or symbol name");
        }
        
    }
}