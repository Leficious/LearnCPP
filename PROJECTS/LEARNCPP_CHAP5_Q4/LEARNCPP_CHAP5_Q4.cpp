// LEARNCPP_CHAP5_Q4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <string_view>

std::string getName(int num) {

    std::cout << "Enter the name of person #" << num << ':';
    std::string name{};
    std::getline(std::cin >> std::ws, name);
    return name;
}

int getAge(std::string_view name)
{
    std::cout << "Enter the age of " << name << ":";
    int age{};
    std::cin >> age;
    return age;
}

void printOlder(std::string_view nameA, int ageA, std::string_view nameB, int ageB)
{
    if (ageA == ageB) {
        std::cout << nameA << " is the same age as " << nameB << ".\n";
        return;
    }
    if (ageA > ageB) {
        std::cout << nameA << " (age " << ageA << ')' << " is older than " << nameB << " (age " << ageB << ").\n";
    }
    else {
        std::cout << nameB << " (age " << ageB << ')' << " is older than " << nameA << " (age " << ageA << ").\n";
    }
}

int main()
{
    const std::string nameA{ getName(1) };
    const int ageA{ getAge(nameA) };

    const std::string nameB{ getName(2) };
    const int ageB{ getAge(nameB) };

    printOlder(nameA, ageA, nameB, ageB);

    return 0;
}

