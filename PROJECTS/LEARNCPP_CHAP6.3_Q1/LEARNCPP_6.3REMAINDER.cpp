// LEARNCPP_6.3REMAINDER.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

constexpr bool isEven(int x) {
    return (x % 2) == 0;
}

int main()
{
    std::cout << "Input an integer: ";
    int x{};
    std::cin >> x;
    if (isEven(x)) {
        std::cout << x << " is " << "even\n";
    }
    else {
        std::cout << x << " is " << "odd\n";
    }
    return 0;
}

