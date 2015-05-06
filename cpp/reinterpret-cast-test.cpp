#include <cstdint>
#include <cassert>
#include <iostream>

int f() { return 42; }

int main()
{
        int i = 7;

        uintptr_t v1 = reinterpret_cast<uintptr_t>(&i); 
        std::cout << "The value of &i is 0x" << std::hex << v1 << '\n';
        int* p1 = reinterpret_cast<int*>(v1);
        assert(p1 == &i);

        void(*fp1)() = reinterpret_cast<void(*)()>(f);
        int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
        std::cout << std::dec << fp2() << '\n'; // safe

        char* p2 = reinterpret_cast<char*>(&i);
        if(p2[0] == '\x7')
                std::cout << "This system is little-endian\n";
        else
                std::cout << "This system is big-endian\n";

        reinterpret_cast<unsigned int&>(i) = 42;
        std::cout << i << '\n';
}
