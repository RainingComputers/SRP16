#include <iostream>

int main()
{
    uint16_t a = 0x8000;
    std::cout << "No shift:" << std::endl;
    std::cout << std::hex << a <<std::endl;
    std::cout << "Right shift:" << std::endl;
    a = ((int16_t)a>>2);
    std::cout << std::hex << a <<std::endl;
}