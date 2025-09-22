// LEARNCPP_CHAP7.3_Q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main() {
	std::cout << "Enter an integer: ";
	int smaller{};  // smaller is created
	std::cin >> smaller;

	std::cout << "Enter a larger integer: ";
	int larger{};   // larger is created
	std::cin >> larger;

	if (smaller > larger) {
		int temp{ smaller }; // temp is created
		smaller = larger;
		larger = temp;
		std::cout << "Swapping the values\n";
	}   // temp is destroyed

	std::cout << "The smaller value is " << smaller << '\n';
	std::cout << "The larger value is " << larger << '\n';
	return 0;
}   // smaller and larger are destroyed

