/*
Basics of Memory Management
*/

#include <iostream>
#include <cstdint>

// declare the type "byte" to use later
typedef uint8_t byte;

int main()
{
    /*
    Static Allocation, compiler assigns a chunk of memory
    The variable data is a pointer the points to the first element the array
    */
    byte data_static[5] = {1, 2, 3, 4, 5};

    // This prints the address of the pointer to the first index, we use static_cast for compile time casting
    std::cout << static_cast<void *>(&data_static) << std::endl;

    // The * is a dereference operator that gets the value that the pointer is looking at
    std::cout << static_cast<int>(*(&data_static[2])) << std::endl;

    /*
    Dynamic Allocation, runtime memory allocation
    */

    // Dynamically allocate memory
    byte *data_new = new byte[5];

    // Deallocated the memory of the values in the array
    delete[] data_new;

    // Also must deallocate the pointer to avoid dangling pointers
    data_new = nullptr;

    // Malloc allocates a block of memory but doesn't initialize the values
    byte *data_malloc = static_cast<byte *>(malloc(5 * sizeof(byte)));

    // Calloc allocates a block of memory and initializes all values to 0
    byte *data_calloc = static_cast<byte *>(calloc(5, sizeof(byte)));

    free(data_malloc);
    free(data_calloc);

    /*
    Stack vs Heap: Statically allocated memory goes on the stack at compile time where as
    dynamically allocated memory goes on heap at runtime. Stack memory is automatically managed by the OS
    and used local variable, return addresses, etc. it is smaller and faster. Heap memory has to be manually
    managed using delete/free it is larger and slower than the stack and stores global values/pointers.
    Stack memory is used for storing temporary values so a deep recursion can lead to a stack overflow
    */

    /*
    Smart pointers can be used for automatic deallocation and preventing dangling pointers
    */

    /*
    Pointer Arithmitic
    */

    byte data[4] = {1, 2, 3, 4};

    byte *ptr = data;

    std::cout << static_cast<int>(*ptr) << std::endl;

    // This allows you to go out of bounds
    std::cout << static_cast<int>(*(ptr + 1)) << std::endl;
}
