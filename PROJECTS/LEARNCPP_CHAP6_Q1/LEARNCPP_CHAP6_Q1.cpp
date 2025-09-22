// LEARNCPP_CHAP6_Q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string_view>

// Write the function getQuantityPhrase() here
std::string_view getQuantityPhrase(int x) {

	if (x < 0) return "negative";
	switch (x) {
	case 0:
		return "no";
	case 1:
		return "a single";
	case 2:
		return "a couple of";
	case 3:
		return "a few";
	default:
		return "many";
	}
}

// Write the function getApplesPluralized() here
std::string_view getApplesPluralized(int x) {
	return (x == 1 ? "apple" : "apples");
}

int main()
{
	constexpr int maryApples{ 3 };
	std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

	std::cout << "How many apples do you have? ";
	int numApples{};
	std::cin >> numApples;

	std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

	return 0;
}
