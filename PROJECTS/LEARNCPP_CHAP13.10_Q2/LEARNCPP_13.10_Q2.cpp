// LEARNCPP_13.10_Q2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
struct Fraction {
	int numerator{};
	int denominator{};
};

Fraction inputFraction() {
	std::cout << "Enter a value for the numerator: ";
	int num{};
	std::cin >> num;

	std::cout << "Enter a value for the denominator: ";
	int denom{};
	std::cin >> denom;

	return { num, denom };
}

constexpr Fraction multiplyFractions(const Fraction& a, const Fraction& b) {
	int num{ a.numerator * b.numerator };
	int denom{ a.denominator * b.denominator };
	return { num, denom };
}

void printFraction(const Fraction& frac) {
	std::cout << "Your fractions multiplied together: "
		<< frac.numerator << '/' << frac.denominator << '\n';
}

int main()
{
	printFraction(multiplyFractions(inputFraction(), inputFraction()));
	return 0;
}

