#include <iostream>
#include <bitset>
#include <cstdint>

int main() {
    std::uint8_t a = 6;          // 0000 0110
    std::uint8_t b = 0b00001011; // 0000 1011
    std::uint8_t c = a & 1;
    std::cout << c << '\n';
    return 0;
}