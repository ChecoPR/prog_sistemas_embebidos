#include <iostream>
#include <bitset>
#include <cstdint>

int main() {
    /*
    std::uint8_t a = 1;

    std::cout << "Inicial:\n";
    std::cout << std::bitset<8>(a) << '\n';

    a <<= 6;
    std::cout << "Despues de a <<= 6:\n";
    std::cout << std::bitset<8>(a) << '\n';

    a >>= 4;
    std::cout << "Despues de a >>= 4:\n";
    std::cout << std::bitset<8>(a) << '\n';

    return 0;
    */
    std::uint32_t a = 1;

    std::cout << "Inicial:\n";
    std::cout << std::bitset<32>(a) << '\n';

    a <<= 32;
    std::cout << "Despues de a <<= 32:\n";
    std::cout << std::bitset<32>(a) << '\n';

    a >>= 4;
    std::cout << "Despues de a >>= 4:\n";
    std::cout << std::bitset<8>(a) << '\n';

    return 0;
}