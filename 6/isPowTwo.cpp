#include <iostream>

bool isPowTwo(uint64_t value)
{
    uint64_t bit = 1;
    do {
        if (value & bit) {
            while (bit <<= 1) {
                if (value & bit) return false;
            }
            return true;
        }
    } while (bit <<= 1);

    return false;
}

int main(int argc, char const *argv[])
{
    uint64_t a0=0, a1=1, a2=8, a3=10, a5=9223372036854775808, a4=a5-1;

    std::cout << isPowTwo(a0) << std::endl; // false
    std::cout << isPowTwo(a1) << std::endl; // true 
    std::cout << isPowTwo(a2) << std::endl; // true
    std::cout << isPowTwo(a3) << std::endl; // false
    std::cout << isPowTwo(a4) << std::endl; // false
    std::cout << isPowTwo(a5) << std::endl; // true
    
    return 0;
}
