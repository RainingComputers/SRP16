#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

namespace cpu
{
    enum spl_regs {A=60, MPTR, SP, PC};

    class srp16cpu
    {
        bool inc_pc;
        bool illegal_instruction;

    public:
        srp16cpu();
        uint16_t instruction_reg;
        uint16_t registers[64];
        uint8_t memory[65536];
        int16_t carry;
        bool flag;

        void step();
        void reset();
        bool illegal();
    };
}

#endif