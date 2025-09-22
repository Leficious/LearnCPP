// LEARNCPP_8.10_Q4_FizzBuzz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void fizzbuzz(int num) {
	for (int i{ 1 }; i <= num; ++i) {
		if (i % 15 == 0) std::cout << "fizzbuzz\n";
		else if (i % 5 == 0) std::cout << "buzz\n";
		else if (i % 3 == 0)std::cout << "fizz\n";
		else std::cout << i << '\n';
	}
}

int main() {
	fizzbuzz(15);
	return 0;
}
