 #include "isa.hpp"

namespace isa
{
    uint16_t pack_etype(int field_0_3, int field_4_7, int field_8_15)
    {
        uint16_t instruction = 0;
        instruction |= field_0_3;
        instruction |= (field_4_7<<4);
        instruction |= (field_8_15<<8);
        return instruction;
    }

    uint16_t pack_ttype(int field_0_3, int field_4_15)
    {
        int16_t instruction = 0;
        instruction |= field_0_3;
        instruction |= (field_4_15<<4);
        return instruction;
    }

    uint16_t pack_rtype(int field_0_3, int field_4_9, int field_10_15)
    {
        int16_t instruction = 0;
        instruction |= field_0_3;
        instruction |= (field_4_9<<4);
        instruction |= (field_10_15<<10);
        return instruction;
    }

    std::string instruction_to_str(uint16_t instruction)
    {
        std::string instruction_str;
        
        /* Construct hex string from int */
        for(int i : {1, 0, 3, 2})
        { 
            /* Get ith 4 bits from int */
            unsigned char digit = (instruction >> (i*4)) & 0x000F;
            /* Convert to valid char */
            if(digit <= 9) digit += 48;
            else digit += 55;
            /* Add to string  */
            instruction_str.push_back(digit);
            /* New line after a byte and the end */
            if(i==0||i==2) instruction_str.push_back('\n');
        }

        return instruction_str;
    }
}