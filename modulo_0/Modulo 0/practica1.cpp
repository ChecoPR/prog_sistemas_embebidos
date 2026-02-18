#include <iostream>
#include <bitset>
#include <cstdint>
#include <limits>
#include <compare>

int main() {

    std::uint32_t raw = 0b10101101'11100110'00000101'00110010;

    std::cout << "Registro crudo:\n";
    std::cout << std::bitset<32>(raw) << "\n\n";

    std::uint32_t sensor_value = raw & 0xFFF;
    std::cout << std::bitset<32>(0xFFF) << "\n";
    std::cout << std::bitset<32>(raw & 0xFFF) << "\n";
    std::cout << "Valor del sensor (bits 0-11): " << sensor_value << "\n"; 

    bool state = (raw >> 12) & 1;
    std::cout << std::bitset<32>(1) << "\n";
    std::cout << std::bitset<32>((raw >> 12) & 1) << "\n";
    std::cout << "Estado (bit 12): " << state << "\n";

    bool error = (raw >> 13) & 1;

    std::cout << std::bitset<32>((raw >> 13) & 1) << "\n";
    std::cout << "Error (bit 13): " << error << "\n";

    std::cout << std::bitset<32>(0b11) << "\n";
    std::cout << std::bitset<32>(raw >> 14) << "\n";
    std::cout << std::bitset<32>((raw >> 14) & 0b11) << "\n";
    std::cout << "Modo de operación (bits 14-15): " << ((raw >> 14) & 0b11) << "\n";

    std::uint8_t temp_raw = (raw >> 16) & 0xFF;
    std::int8_t temperature = static_cast<std::int8_t>(temp_raw);

    std::cout << std::bitset<32>(raw >> 16) << "\n";
    std::cout << std::bitset<32>(0xFF) << "\n";
    std::cout << std::bitset<32>((raw >> 16) & 0xFF) << "\n";

    std::cout << int(temp_raw) << "\n";
    std::cout << int(temperature) << "\n";


    std::uint32_t test = ((raw >> 16) << 1);
    std::cout << std::bitset<32>(test) << "\n";

}