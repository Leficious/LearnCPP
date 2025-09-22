// LEARNCPP_CHAP7_Q3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int accumulate(int x) {
    static int accumulateVal{};
    return accumulateVal += x;
}

int requestInput() {
    std::cout << "Enter a number: ";
    int temp{};
    std::cin >> temp;
    return temp;
}

int main()
{
    std::cout << accumulate(requestInput()) << '\n';
    std::cout << accumulate(requestInput()) << '\n';
    std::cout << accumulate(requestInput()) << '\n';
    return 0;
}