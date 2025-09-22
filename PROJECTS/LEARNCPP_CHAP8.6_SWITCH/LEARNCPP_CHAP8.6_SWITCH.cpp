// LEARNCPP_CHAP8.6_SWITCH.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

float calculate(int x, int y, char z) {
	switch (z) {
	case '+':
		return x + y;
	case '-':
		return x - y;
	case '*':
		return x * y;
	case '/':
		if (y == 0) {
			std::cout << "error: divide by 0\n";
			return 0.f;
		}
		float newX;
		newX = static_cast<float>(x);
		float newY;
		newY = static_cast<float>(y);
		return newX / newY;
	default:
		std::cout << "invalid operator entered\n";
		return 0.f;
	}
}

int enterInt() {
	std::cout << "enter an integer: ";
	int x{};
	std::cin >> x;
	return x;
}

char enterOp() {
	std::cout << "| + | - | * | / |\nenter an operator: ";
	char x{};
	std::cin >> x;
	return x;
}

int main() {

	int val1{ enterInt() };
	int val2{ enterInt() };
	char op{ enterOp() };
	float result{ calculate(val1, val2, op) };
	std::cout << result << '\n';
	return 0;
}
