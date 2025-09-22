// LEARNCPP_OBIT_Q6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdint>
#include <format>

/*constexpr bool isOdd(int x) {
    return (x % 2 == 1);
}

int main()
{
    constexpr std::uint8_t mask0{ 0b0000'0001 };
    constexpr std::uint8_t mask1{ 0b0000'0010 };
    constexpr std::uint8_t mask2{ 0b0000'0100 };
    constexpr std::uint8_t mask3{ 0b0000'1000 };
    constexpr std::uint8_t mask4{ 0b0001'0000 };
    constexpr std::uint8_t mask5{ 0b0010'0000 };
    constexpr std::uint8_t mask6{ 0b0100'0000 };
    constexpr std::uint8_t mask7{ 0b1000'0000 };

    std::cout << "Input a number between 0 and 255: ";
    int x{};
    std::cin >> x;

    std::uint8_t num{0b0000'0000};
    if (x >= 128 && isOdd(x/128)) {
        num |= mask7;
    }
    if (x >= 64 && isOdd(x/64)) {
        num |= mask6;
    }
    if (x >= 32 && isOdd(x/32)) {
        num |= mask5;
    }
    if (x >= 16 && isOdd(x/16)) {
        num |= mask4;
    }
    if (x >= 8 && isOdd(x/8)) {
        num |= mask3;
    }
    if (x >= 4 && isOdd(x/4)) {
        num |= mask2;
    }
    if (x >= 2 && isOdd(x/2)) {
        num |= mask1;
    }
    if (x >= 1 && isOdd(x/1)) {
        num |= mask0;
    }
    std::cout << std::format("{:b}\n", x);
    return 0;
}*/

void printBit(int x, int pow)
{
    std::cout << ((x / pow) % 2);
}

void print8BitBinary(int x)
{
    printBit(x, 128);
    printBit(x, 64);
    printBit(x, 32);
    printBit(x, 16);

    std::cout << ' ';

    printBit(x, 8);
    printBit(x, 4);
    printBit(x, 2);
    printBit(x, 1);
}

int main()
{
    std::cout << "Enter an integer between 0 and 255: ";
    int x{};
    std::cin >> x;

    print8BitBinary(x);

    std::cout << '\n';

    return 0;
}
