// LEARNCPP_CHAP16.6_Q6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string_view>
#include <cassert>

int main()
{
    std::vector divisors{ 3, 5, 7, 11, 13, 17, 19 };
    std::vector<std::string_view> words{"fizz", "buzz", "pop", "bang", "jazz", "pow", "boom"};
    assert(divisors.size() == words.size() && "fizzbuzz: array sizes don't match\n");

    for (int i{ 1 }; i < 151; ++i) {
        bool printed{ false };
        for (std::size_t n{ 0 }; n < divisors.size(); ++n) {
            if (i % divisors[n] == 0) {
                std::cout << words[n];
                printed = true;
            }
        }
        if (!printed) std::cout << i;
        std::cout << '\n';
    }
    return 0;
}
