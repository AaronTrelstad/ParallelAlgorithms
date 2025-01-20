/*
Basic bitwise operations
*/

#include <iostream>
#include <bitset>

bool check_bit(int value, int bit)
{
    return value & (1 << bit);
}

int main()
{
    int a = 0b1010;
    int b = 0b0011;

    std::cout << "a " << std::bitset<4>(a) << std::endl;
    std::cout << "b " << std::bitset<4>(b) << std::endl;

    std::cout << "AND (a&b) " << std::bitset<4>(a & b) << std::endl;
    std::cout << "OR (a|b) " << std::bitset<4>(a | b) << std::endl;
    std::cout << "XOR (a^b) " << std::bitset<4>(a ^ b) << std::endl;
    std::cout << "NOT (a) " << std::bitset<4>(~a) << std::endl;

    // Shifting left is mulitplying by 2
    std::cout << "Shift left " << std::bitset<4>(a << 2) << std::endl;

    // Shift right is dividing by 2
    std::cout << "Shift right " << std::bitset<4>(a >> 2) << std::endl;

    // Bit Masking to extract a specific bit
    std::cout << check_bit(0b1010, 1) << std::endl;
}
