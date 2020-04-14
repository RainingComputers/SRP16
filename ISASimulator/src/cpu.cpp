#include "cpu.hpp"

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

    static int16_t register_overflow(uint16_t op1, uint16_t op2, int16_t carry=0)
    {
        /* 
            Cast to int32 from int16 and add operands and carry,
            if there is overflow, it can be detected with mask 
            0xffff0000
        */
        int32_t result_with_overflow = (int32_t)op1 + (int32_t)op2 + (int32_t)carry;
        int16_t new_carry = (result_with_overflow & 0xffff0000) > 0;

        return new_carry;
    }

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
        /* Initial state for cpu */
        registers[MPTR] = 0;
        registers[PC] = 0;
        registers[SP] = 0xffff;
        flag = false;
        inc_pc = true;
        illegal_instruction = false;
        carry = 0;
    }

    bool srp16cpu::illegal()
    {
        return illegal_instruction;
    }

    void srp16cpu::step()
    {
        inc_pc = true;
        illegal_instruction = false;

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
                uint8_t upper = registers[e_type_reg1] >> 8;
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
                /* STB@MPTR Instruction */
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

                break;
            }

            case 0b1010:
            {
                /* SJMP Instruction */
                registers[PC] += t_type_imm_sign;
                inc_pc = false; 
                break;
            }

            case 0b1011:
            {
                /* SJMPF Instruction */
                if(flag)
                {
                    registers[PC] += t_type_imm_sign;
                    inc_pc = false; 
                }
                break;
            }

            case 0b1100:
            {
                /* R-type opcode1=1100 Instructions */
                switch (r_type_opcode2)
                {
                    case 0b111011:
                    {
                        /* LDAU Instruction */
                        registers[A] = 
                            (r_type_imm << 12) | (registers[A] & 0x0fff);
                        break;
                    }

                    case 0b111100:
                    {
                        /* POP Instruction */
                        if(r_type_reg2 > 31)
                            illegal_instruction = true;
                        else
                        {
                            uint16_t lower = memory[registers[SP]];
                            uint16_t upper = memory[registers[SP]+1];
                            registers[r_type_reg2] = (upper << 8) | lower;
                            registers[SP]+=2;
                        }

                        break;
                    }

                    case 0b111101:
                    {
                        /* PUSH Instruction */
                        if(r_type_reg2 > 31)
                            illegal_instruction = true;
                        else
                        {
                            uint16_t lower = registers[r_type_reg2];
                            uint16_t upper = (registers[r_type_reg2] >> 8);
                            memory[registers[SP]-1] = upper;
                            memory[registers[SP]-2] = lower;
                            registers[SP]-=2;
                        }

                        break;
                    }

                    case 0b111110:
                    {
                        /* INC Instruction */
                        if(r_type_reg2 > 31)
                            illegal_instruction = true;
                        else
                        {
                            registers[r_type_reg2]++;
                        }

                        break;
                    }

                    case 0b111111:
                    {
                        /* DEC Instruction */
                        if(r_type_reg2 > 31)
                            illegal_instruction = true;
                        else
                        {
                            registers[r_type_reg2]--;
                        }

                        break;                        
                    }

                    case 0b100011:
                    {
                        /* SLAI Instruction */
                        /* TODO: Remove this instructon */
                        registers[A] = (int16_t)registers[A] << r_type_imm;

                        break;
                    }

                    case 0b100100:
                    {
                        /* SRAI Instruction */
                        /* Cast to signed int so that c++ performs arithmatic shift */
                        registers[A] = (int16_t)registers[A] >> r_type_imm;
                        break;
                    }

                    case 0b100101:
                    {
                        /* SLLI Instruction */
                        registers[A] <<= r_type_imm;

                        break;
                    }

                    case 0b100110:
                    {
                        /* SRLI Instruction */
                        registers[A] >>= r_type_imm;

                        break;
                    }

                    case 0b000001:
                    {
                        /* ADD Instrucion */
                        carry = register_overflow(registers[A], registers[r_type_reg2]);
                        registers[A] += registers[r_type_reg2];

                        break;
                    }

                    case 0b000010:
                    {
                        /* SUB Instrucion */
                        carry = register_overflow(registers[A], -1*registers[r_type_reg2]);
                        registers[A] -= registers[r_type_reg2];

                        break;
                    }

                    case 0b001101:
                    {
                        /* ADC Instruction */
                        carry = register_overflow(registers[A], registers[r_type_reg2],
                            carry);
                        registers[A] += registers[r_type_reg2] + carry;

                        break;
                    }

                    case 0b001110:
                    {
                        /* SBB Instrution */
                        carry = register_overflow(registers[A], ~registers[r_type_reg2],
                            carry);
                        registers[A] += (~registers[r_type_reg2] + carry);

                        break;                        
                    }

                    case 0b000111:
                    {
                        /* AND Instruction */
                        registers[A] &= registers[r_type_reg2];

                        break;
                    }

                    case 0b001000:
                    {
                        /* OR Instruction */
                        registers[A] |= registers[r_type_reg2];

                        break;
                    }

                    case 0b001001:
                    {
                        /* XOR Instruction */
                        registers[A] ^= registers[r_type_reg2];

                        break;
                    }

                    case 0b000011:
                    {
                        /* SLA Instruction */
                        /* TODO: Remove this instructon */
                        registers[A] = (int16_t)registers[A] << registers[r_type_reg2];

                        break;
                    }

                    case 0b000100:
                    {
                        /* SRA Instruction */
                        /* Cast to signed int so that c++ performs arithmatic shift */
                        registers[A] = (int16_t)registers[A] >> registers[r_type_reg2];

                        break;
                    }

                    case 0b000101:
                    {
                        /* SLL Instruction */
                        registers[A] <<= registers[r_type_reg2];

                        break;
                    }

                    case 0b000110:
                    {
                        /* SRL Instruction */
                        registers[A] >>= registers[r_type_reg2];

                        break;
                    }

                    case 0b001010:
                    {
                        /* CL Instruction */
                        if(registers[A] < registers[r_type_reg2]) flag = true;
                        else flag = false;

                        break;
                    }

                    case 0b001011:
                    {
                        /* CG Instruction */
                        if(registers[A] > registers[r_type_reg2]) flag = true;
                        else flag = false;

                        break;
                    }

                    case 0b001100:
                    {
                        /* CE Instruction */
                        if(registers[A] == registers[r_type_reg2]) flag = true;
                        else flag = false;

                        break;
                    }

                    case 0b010000:
                    {
                        switch(r_type_opcode3)
                        {

                            case 0b000000:
                            {
                                /* NOTF Instruction */
                                flag = !flag;
                                break;
                            }
                            
                            default:
                            {
                                illegal_instruction = true;
                            }
                        }
                    }
                }

                break;
            }

            case 0b1101:
            {
                switch (e_type_opcode2)
                {
                    case 0b0001:
                    {
                        /* ADDI Instruction */
                        carry = register_overflow(registers[A], e_type_imm_sign);
                        registers[A] += e_type_imm_sign;

                        break;

                    }

                    case 0b0111:
                    {
                        /* ANDI Instruction */
                        registers[A] &= e_type_imm_sign;
                        
                        break;
                    }

                    case 0b1000:
                    {
                        /* ORI Instruction */
                        registers[A] |= e_type_imm_sign;
                        
                        break;
                    }

                    case 0b1001:
                    {
                        /* XORI Instruction */
                        registers[A] ^= e_type_imm_sign;
                        
                        break;
                    }

                    case 0b1010:
                    {
                        /* CLI Instruction */
                        if(registers[A] < e_type_imm_sign) flag = true;
                        else flag = false;

                        break;
                    }

                    case 0b1011:
                    {
                        /* CGI Instruction */
                        if(registers[A] > e_type_imm_sign) flag = true;
                        else flag = false;

                        break;
                    }

                    case 0b1100:
                    {
                        /* CEI Instruction */
                        if(registers[A] == e_type_imm_sign) flag = true;
                        else flag = false;

                        break;
                    }

                    case 0b1101:
                    {
                        /* ADCI Instruction */
                        carry = register_overflow(registers[A], e_type_imm_sign,
                            carry);
                        registers[A] += e_type_imm_sign + carry;

                        break;
                    }

                    case 0b1110:
                    {
                        /* SBBI Instruction */
                        carry = register_overflow(registers[A], ~e_type_imm_sign,
                            carry);
                        registers[A] += (~e_type_imm_sign + carry);

                        break;
                    }

                    default:
                    {
                        illegal_instruction = true;
                    }
                }
            }

            default:
            {
                illegal_instruction = true;
            }
        }

        /* Increment program counter */
        if(inc_pc) registers[PC]+=2;
    }
}