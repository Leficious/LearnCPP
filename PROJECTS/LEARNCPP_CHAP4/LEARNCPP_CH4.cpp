// LEARNCPP_CH4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/** 
*   Write the following program: The user is asked to enter 2 floating point numbers (use doubles). 
*   The user is then asked to enter one of the following mathematical symbols: +, -, *, or /. 
*   The program computes the answer on the two numbers the user entered and prints the results. If the user enters an invalid symbol,
*   the program should print nothing. 
*/

#include <iostream>

int main()
{
    std::cout << "Enter a decimal number ";
    double a{};
    std::cin >> a;

    std::cout << "Enter another decimal number ";
    double b{};
    std::cin >> b;

    std::cout << "Enter one of the following:\n + - * /:\n ";
    char op;
    std::cin >> op;

    switch (op){
    case '+':
        std::cout << a+b;
        break;
    case '-':
        std::cout << a-b;
        break;
    case '*':
        std::cout << a*b;
        break;
    case '/':
        std::cout << a/b;
        break;
    default:
        break;
    }

    return 0;
}

