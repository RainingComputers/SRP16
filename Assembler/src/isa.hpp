#ifndef ISA_HPP
#define ISA_HPP

#include <cstdint>
#include <string>
#include <map>

namespace isa
{
    /* Functions for creating an instrution word */
    uint16_t pack_etype(int field_0_3, int field_4_7, int field_8_15);
    uint16_t pack_ttype(int field_0_3, int field_4_15);
    uint16_t pack_rtype(int field_0_3, int field_4_9, int field_10_15);

    /* Types of immediates */
    enum imm_type{SIGNED, UNSIGNED, NOIMM};

    /* instruction types */
    enum inst_type{E_TYPE_LOAD, T_TYPE_LOAD, R_TYPE_LOAD, R_TYPE_MOV, 
        T_TYPE_JUMP, R_TYPE_STACK, R_TYPE_INCDEC, E_TYPE_IMM_ARITH,
        R_TYPE_IMM_ARITH, R_TYPE_ARITH, E_TYPE_CMP_IMM, R_TYPE_CMP,
        R_TYPE_FLAG};

    /* enum for diffrent types of operands */
    enum oper_type{REGISTER, GPREGISTER, LREGISTER, IMMEDIATE, RIMMEDIATE};

    /* For not applicable */
    const int NA = -1;

    /* struct for holding instruction properties */
    struct property
    {
        inst_type instr_type;
        imm_type immediate_type;
        int opcode1;
        int opcode2;
        int opcode3;
    };
    
    /* struct for holding foramt/syntax for diffrent types of instruction */
    struct format
    {
        int operand_type[2];
        int immediate_size;
        int no_operands;
    };

    /* Defines properties of every instruction */
    extern std::map<std::string, property> instr_properties;
    
    /* Defines instr syntax/format for every instruction type */
    extern format instr_formats[];

}
#endif