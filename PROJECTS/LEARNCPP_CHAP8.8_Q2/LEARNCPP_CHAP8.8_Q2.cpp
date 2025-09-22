// LEARNCPP_CHAP8.8_Q2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main(){

    char init{ 'a' };
    while (init <= 'z') {
        std::cout << init << "  " << static_cast<int>(init) << '\n';
        ++init;
    }
}

