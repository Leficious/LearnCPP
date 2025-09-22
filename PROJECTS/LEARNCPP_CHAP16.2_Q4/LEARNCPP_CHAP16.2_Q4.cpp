// LEARNCPP_CHAP16.2_Q4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

int main(){
    std::vector<int> nums(3);
    std::cout << "Enter 3 integers: ";
    std::cin >> nums[0] >> nums[1] >> nums[2];
    std::cout << "The sum is: " << nums[0] + nums[1] + nums[2] << '\n';
    std::cout << "The product is: " << nums[0] * nums[1] * nums[2] << '\n';
    return 0;
}