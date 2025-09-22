// LEARNCPP_8.10_Q4_FizzBuzz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void fizzbuzz(int num) {
	for (int i{ 1 }; i <= num; ++i) {
		if (i % 3 == 0)std::cout << "fizz";
		if (i % 5 == 0) std::cout << "buzz";
		if (i % 7 == 0) std::cout << "pop";
		if (i % 7 != 0 && i % 5 != 0 && i % 3 != 0) 
			std::cout << i;
		std::cout << '\n';
	}
}

int main() {
	fizzbuzz(150);
	return 0;
}
