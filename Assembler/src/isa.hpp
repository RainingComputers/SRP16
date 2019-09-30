#ifndef ISA_HPP
#define ISA_HPP

#include <cstdint>
#include <string>

namespace isa
{
    uint16_t pack_etype(int field_0_3, int field_4_7, int field_8_15);
    uint16_t pack_ttype(int field_0_3, int field_4_15);
    uint16_t pack_rtype(int field_0_3, int field_4_9, int field_10_15);
    std::string instruction_to_str(uint16_t instruction);

}

#endif