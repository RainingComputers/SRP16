 #include "isa.hpp"

namespace isa
{
    /* Define properties of every instruction */
    std::map<std::string, property> instr_properties = {
        {"ldr",     {E_TYPE_LOAD, SIGNED, 0b0000, NA, NA}},
        {"ldru",    {E_TYPE_LOAD, UNSIGNED, 0b0001, NA, NA}},
        {"ld@mptr", {E_TYPE_LOAD, SIGNED, 0b0010, NA, NA}},
        {"st@mptr", {E_TYPE_LOAD, SIGNED, 0b0011, NA, NA}},
        {"ldb@mptr",{E_TYPE_LOAD, SIGNED, 0b0100, NA, NA}},
        {"stb@mptr",{E_TYPE_LOAD, SIGNED, 0b0101, NA, NA}},
        {"lda",     {T_TYPE_LOAD, SIGNED, 0b0110, NA, NA}},
        {"ldmptr",  {T_TYPE_LOAD, UNSIGNED, 0b0111, NA, NA}},
        {"ldmptru", {T_TYPE_LOAD, UNSIGNED, 0b1000, NA, NA}},
        {"ldau",    {R_TYPE_LOAD, UNSIGNED, 0b1100, 0b111011, NA}},
        {"mov",     {R_TYPE_MOV, NOIMM, 0b1001, NA, NA}},
        {"jmp",     {R_TYPE_MOV, NOIMM, 0b1001, NA, NA}},
        {"sjmp",    {T_TYPE_JUMP, SIGNED, 0b1010, NA, NA}},
        {"sjmpf",   {T_TYPE_JUMP, SIGNED, 0b1011, NA, NA}},
        {"pop",     {R_TYPE_STACK, NOIMM, 0b1100, 0b111100, NA}},
        {"push",    {R_TYPE_STACK, NOIMM, 0b1100, 0b111101, NA}},
        {"inc",     {R_TYPE_INCDEC, NOIMM, 0b1100, 0b111110, NA}},
        {"dec",     {R_TYPE_INCDEC, NOIMM, 0b1100, 0b111111, NA}},
        {"addi",    {E_TYPE_IMM_ARITH, SIGNED, 0b1101, 0b0001, NA}},
        {"adci",    {E_TYPE_IMM_ARITH, SIGNED, 0b1101, 0b1101, NA}},
        {"sbbi",    {E_TYPE_IMM_ARITH, SIGNED, 0b1101, 0b1110, NA}},
        {"andi",    {E_TYPE_IMM_ARITH, SIGNED, 0b1101, 0b0111, NA}},
        {"ori",     {E_TYPE_IMM_ARITH, SIGNED, 0b1101, 0b1000, NA}},
        {"xori",    {E_TYPE_IMM_ARITH, SIGNED, 0b1101, 0b1001, NA}},
        {"slai",    {R_TYPE_IMM_ARITH, UNSIGNED, 0b1100, 0b100011, NA}},
        {"srai",    {R_TYPE_IMM_ARITH, UNSIGNED, 0b1100, 0b100100, NA}},
        {"slli",    {R_TYPE_IMM_ARITH, UNSIGNED, 0b1100, 0b100101, NA}},
        {"srli",    {R_TYPE_IMM_ARITH, UNSIGNED, 0b1100, 0b100110, NA}},
        {"add",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b000001, NA}},
        {"sub",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b000010, NA}},
        {"adc",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b001101, NA}},
        {"sbb",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b001110, NA}},
        {"and",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b000111, NA}},
        {"or",      {R_TYPE_ARITH, NOIMM, 0b1100, 0b001000, NA}},
        {"xor",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b001001, NA}},
        {"sla",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b000011, NA}},
        {"sra",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b000100, NA}},
        {"sll",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b000101, NA}},
        {"srl",     {R_TYPE_ARITH, NOIMM, 0b1100, 0b000110, NA}},
        {"cli",     {E_TYPE_CMP_IMM, SIGNED, 0b1101, 0b1010, NA}},
        {"cgi",     {E_TYPE_CMP_IMM, SIGNED, 0b1101, 0b1011, NA}},
        {"cei",     {E_TYPE_CMP_IMM, SIGNED, 0b1101, 0b1100, NA}},
        {"cl",      {R_TYPE_CMP, NOIMM, 0b1100, 0b001010, NA}},
        {"cg",      {R_TYPE_CMP, NOIMM, 0b1100, 0b001011, NA}},
        {"ce",      {R_TYPE_CMP, NOIMM, 0b1100, 0b001100, NA}},
        {"notf",    {R_TYPE_FLAG, NOIMM, 0b1100, 0b010000, 0b000000}}
    };

    /* Define instruction syntax/format for every instr type */
    format instr_formats[] = {
        /* E_TYPE_LOAD,      */  {{GPREGISTER, IMMEDIATE}, 8, 2}, 
        /* T_TYPE_LOAD,      */  {{IMMEDIATE, NA}, 12, 1},
        /* R_TYPE_LOAD,      */  {{IMMEDIATE, NA}, 6, 1},
        /* R_TYPE_MOV,       */  {{REGISTER, REGISTER}, NA, 2},
        /* T_TYPE_JUMP,      */  {{IMMEDIATE, NA}, 12, 1},
        /* R_TYPE_STACK,     */  {{GPREGISTER, NA}, NA, 1},
        /* R_TYPE_INCDEC,    */  {{GPREGISTER, NA}, NA, 1},
        /* E_TYPE_IMM_ARITH, */  {{IMMEDIATE, NA}, 8, 1},
        /* R_TYPE_IMM_ARITH, */  {{IMMEDIATE, NA}, 6, 1},
        /* R_TYPE_ARITH,     */  {{REGISTER, NA}, NA, 1},
        /* E_TYPE_CMP_IMM,   */  {{IMMEDIATE, NA}, 8, 1},
        /* R_TYPE_CMP,       */  {{REGISTER, NA}, NA, 1},
        /* R_TYPE_FLAG,      */  {{NA, NA}, NA, 0}
    };

    uint16_t pack_etype(int field_0_3, int field_4_7, int field_8_15)
    {
        uint16_t instr = 0;
        instr |= field_0_3;
        instr |= (field_4_7<<4);
        instr |= (field_8_15<<8);
        return instr;
    }

    uint16_t pack_ttype(int field_0_3, int field_4_15)
    {
        int16_t instr = 0;
        instr |= field_0_3;
        instr |= (field_4_15<<4);
        return instr;
    }

    uint16_t pack_rtype(int field_0_3, int field_4_9, int field_10_15)
    {
        int16_t instr = 0;
        instr |= field_0_3;
        instr |= (field_4_9<<4);
        instr |= (field_10_15<<10);
        return instr;
    }
}