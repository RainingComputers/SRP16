#include "cpu.hpp"
#include "hexstr.hpp"

namespace cpu
{
    enum field
    {
        OPCODE1, E_TYPE_OPCODE2,
        R_TYPE_OPCODE2, R_TYPE_OPCODE3, E_TYPE_REG1,
        R_TYPE_REG1, R_TYPE_REG2, E_TYPE_IMM, E_TYPE_IMM_SIGN,
        T_TYPE_IMM, T_TYPE_IMM_SIGN, R_TYPE_IMM, E_TYPE_OFFSET,
        T_TYPE_OFFSET
    };

    static uint16_t get_field(uint16_t word, field instr_field)
    {
        switch (instr_field)
        {
            case OPCODE1:
                return word & 0x000f; 
                break;
            case E_TYPE_OPCODE2:
            case E_TYPE_REG1:
                return (word & 0x00f0) >> 4;
                break;
            case R_TYPE_REG1:
            case R_TYPE_OPCODE2:
                return (word & 0x03f0) >> 4;
                break;
            case R_TYPE_REG2:
            case R_TYPE_OPCODE3:
            case R_TYPE_IMM:
                return (word & 0xfc00) >> 10;
                break;
            case E_TYPE_IMM:
                return (word & 0xff00) >> 8;
                break;
            case E_TYPE_OFFSET:
            case E_TYPE_IMM_SIGN:
            {            
                uint16_t imm_e = ((word & 0xff00) >> 8);
                if(imm_e > 127) return imm_e | 0xff80;
                else return imm_e;
                break;
            }
            case T_TYPE_IMM:
                return (word & 0xfff0) >> 4;
                break;
            case T_TYPE_OFFSET:
            case T_TYPE_IMM_SIGN: 
            {
                uint16_t imm_t = ((word & 0xfff0) >> 4);
                if(imm_t > 2047) return imm_t | 0xf800;
                else return imm_t;
                break;
            }
        }
    }

    srp16cpu::srp16cpu()
    {
        reset();
    }

    void srp16cpu::reset()
    {
        registers[MPTR] = 0;
        registers[PC] = 0;
        flag = false;
        inc_pc = true;
    }

    void srp16cpu::step()
    {
        inc_pc = true;

        /* Load instruction from memory */
        uint16_t instruction_lower = memory[registers[PC]];
        uint16_t instruction_upper = memory[registers[PC]+1];
        uint16_t instruction = (instruction_upper << 8) | instruction_lower;
        instruction_reg = instruction;
        
        /* Decode the instruction */
        uint16_t opcode1 = get_field(instruction, OPCODE1);
        uint16_t e_type_opcode2 = get_field(instruction, E_TYPE_OPCODE2);
        uint16_t e_type_reg1 = get_field(instruction, E_TYPE_REG1);
        uint16_t r_type_reg1 = get_field(instruction, R_TYPE_REG1);
        uint16_t r_type_opcode2 = get_field(instruction, R_TYPE_OPCODE2);
        uint16_t r_type_reg2 = get_field(instruction, R_TYPE_REG2);
        uint16_t r_type_opcode3 = get_field(instruction, R_TYPE_OPCODE3);
        uint16_t r_type_imm = get_field(instruction, R_TYPE_IMM);
        uint16_t e_type_imm = get_field(instruction, E_TYPE_IMM);
        uint16_t e_type_offset = get_field(instruction, E_TYPE_OFFSET);
        uint16_t e_type_imm_sign = get_field(instruction, E_TYPE_IMM_SIGN);
        uint16_t t_type_imm = get_field(instruction, T_TYPE_IMM);
        uint16_t t_type_offset = get_field(instruction, T_TYPE_OFFSET);
        uint16_t t_type_imm_sign = get_field(instruction, T_TYPE_IMM_SIGN);

        /* Simulate the instruction */
        switch (opcode1)
        {
            case 0b0000:
                /* LDR Instruction */
                registers[e_type_reg1] = e_type_imm_sign;
                break;

            case 0b0001:
                /* LDRU Instruction */
                registers[e_type_reg1] = 
                    (e_type_imm << 8) | (registers[e_type_reg1] & 0x00ff);
                break;

            case 0b0010:
            {
                /* LD@MPTR Instruction */
                uint16_t lower = memory[registers[MPTR]];
                uint16_t upper = memory[registers[MPTR]+1];
                registers[e_type_reg1] = (upper << 8) | lower;
                registers[MPTR] += e_type_imm_sign;
                break;
            }

            case 0b0011:
            {
                /* ST@MPTR Instruction */
                uint8_t lower = registers[e_type_reg1];
                uint8_t upper = registers[e_type_reg1] << 8;
                memory[registers[MPTR]] = lower;
                memory[registers[MPTR]+1] = upper;
                registers[MPTR] += e_type_imm_sign;
                break;
            }

            case 0b0100:
            {
                /* LDB@MPTR Instruction */
                uint16_t lower = memory[registers[MPTR]];
                registers[e_type_reg1] = lower;
                registers[MPTR] += e_type_imm_sign;
                break;
            }
            
            case 0b0101:
            {
                /* ST@MPTR Instruction */
                uint8_t lower = registers[e_type_reg1];
                memory[registers[MPTR]] = lower;
                registers[MPTR] += e_type_imm_sign;
                break;  
            }

            case 0b0110:
                /* LDA Instruction */
                registers[A] = t_type_imm_sign;
                break;

            case 0b0111:
                /* LDMPTR Instruction */ 
                registers[MPTR] = t_type_imm;
                break;

            case 0b1000:
                /* LDMPTRU Instruction */
                registers[MPTR] = 
                    (t_type_imm << 12) | (registers[MPTR] & 0x0fff);
                break;

            case 0b1001:
            {
                /* MOV Instruction */
                if(r_type_reg2 == PC)
                    registers[r_type_reg1] = registers[PC]+4;
                else
                    registers[r_type_reg1] = registers[r_type_reg2];

                if(r_type_reg1 == PC) inc_pc = false;
            }
        }

        /* Increment program counter */
        if(inc_pc) registers[PC]+=2;


    }
}