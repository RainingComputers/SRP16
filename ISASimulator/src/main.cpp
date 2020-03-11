/*
    SRP16 ISA Simulator
*/

#include <iostream>
#include <fstream>
#include <string>

#include "cpu.hpp"
#include "hexstr.hpp"

void print_usage()
{
    std::cout<<"srp16sim DHEXFILE"<<std::endl;  
}

void print_reg(cpu::srp16cpu& cpu)
{
    std::cout << "IR = " << int_to_hex<uint16_t>(cpu.instruction_reg) << std::endl;
    std::cout << "PC = " << int_to_hex<uint16_t>(cpu.registers[cpu::PC]) << std::endl;
    std::cout << "A = " << int_to_hex<uint16_t>(cpu.registers[cpu::A]) << std::endl;
    std::cout << "MPTR = " << int_to_hex<uint16_t>(cpu.registers[cpu::MPTR]) << std::endl;
    std::cout << "SP = " << int_to_hex<uint16_t>(cpu.registers[cpu::SP]) << std::endl;
    
    for(int i = 0; i < 32; i++)
    {
        std::cout<<"R"<<i<<" = ";
        std::cout<<int_to_hex<uint16_t>(cpu.registers[i])<<std::endl;
    }
}

void invalid_command()
{
    std::cout << "Invalid command." << std::endl;
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

    /* Load program into memory */
    std::string line;
    int address_count = 0;
    while(std::getline(input_file, line))
    {
        vcpu.memory[address_count] = std::stoi(line, 0, 16);
        address_count+=1;
    }

    /* Start simulation */
    while(true)
    {
        std::string command;
        
        /* Interactive command prompt */
        std::cout << ">>> ";
        std::cin >> command;

        /* Simulator commands */
        if(command == "step" || command == "s")
            vcpu.step();
        else if(command == "reg")
            print_reg(vcpu);
        else if(command == "exit")
            return EXIT_SUCCESS;
        else if(command.substr(0, 3) == "mem")
        {
            int colon_pos = -1;

            /* Syntax check the command */
            if(command[3] != '[' || command.back() != ']')
            {
                invalid_command();
                continue;
            }

            for(int i = 4; i < command.length()-1; i++)
            {
                char c = command[i];

                /* Check proper usage of range(:) symbol */
                if(c == ':')
                    if(i > 4 && colon_pos != -1) 
                    {
                        colon_pos = i;
                        continue;
                    }
                    else 
                    {
                        invalid_command();
                        break;
                    }

                /* Check if valid hex digit */
                if(!(isdigit(c) || (c>='a' && c<='f')))
                {
                    invalid_command();
                    break;
                }
            }

            /* Parse the command */

        }
        else
            invalid_command();
        
    }
}