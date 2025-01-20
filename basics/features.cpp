/*
C++ language features
*/

#include <iostream>

volatile int hardware_register = 10;

constexpr int square(int x)
{
    return x * x;
}

void modify_register()
{
    for (int i = 0; i < 5; i++)
    {
        hardware_register += 1;
        std::cout << "value: " << hardware_register << std::endl;
    }
}

int main()
{
    /*
    Constexpr allows you to compute values at compile time
    */
    constexpr int result = square(5);
    std::cout << result << std::endl;

    /*
    Volatile tells the compiler that the value may change at any time
    so it prevents certain optimizations requiring that the value
    is always read from memory. This is used for things like hardware registers
    and multithreading, where memory could be shared and updated
    */

    modify_register();

    /*
    You can write inline asm using asm()
    */
}
