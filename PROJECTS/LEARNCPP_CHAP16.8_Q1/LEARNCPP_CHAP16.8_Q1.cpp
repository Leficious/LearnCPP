// LEARNCPP_CHAP16.8_Q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <string_view>

template <typename T>
bool isValueInArray(const std::vector<T>& arr, const T& val) {
    for (const auto& n : arr) {
        if (val == n) {
            return true;
        }
    }
    return false;
}

int main() 
{
    std::vector<std::string_view> arr{ "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };
    std::cout << "Enter a name: ";
    std::string name{};
    std::cin >> name;
    
    if (isValueInArray(arr, static_cast<std::string_view>(name))) std::cout << name << " was found.\n";
    else std::cout << name << " was not found.\n";
    return 0;
}

/*

Enter a name: Betty
Betty was found.
Enter a name: Megatron
Megatron was not found.

*/