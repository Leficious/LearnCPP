// LEARNCPP_8.10_Q2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int sumTo(int value) {
    int outVal{};
    for (int i{ value }; i > 0; --i){
        outVal += i;
    }
    return outVal;
}

int main()
{
    std::cout << sumTo(5) << '\n';
    return 0;
}

