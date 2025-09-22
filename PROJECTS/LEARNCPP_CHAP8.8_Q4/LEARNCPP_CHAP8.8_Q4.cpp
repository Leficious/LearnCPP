// LEARNCPP_CHAP8.8_Q4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main() {

	int outer{ 5 };
	int printSpace{ 1 };
	while (outer > 0) {

		int inner{ 5 };
		while (inner > 0) {
			if (inner > printSpace) {
				std::cout << "  ";
				--inner;
			}
			else {
				std::cout << inner-- << ' ';
			}
		}
		std::cout << '\n';
		--outer;
		++printSpace;
	}
	return 0;
}

#include <iostream>

int main()
{
	int outer{ 1 };

	while (outer <= 5)
	{
		// Row elements appear in descending order, so start from 5 and loop through to 1
		int inner{ 5 };

		while (inner >= 1)
		{
			// The first number in any row is the same as the row number
			// So number should be printed only if it is <= the row number, space otherwise
			if (inner <= outer)
				std::cout << inner << ' '; // print the number and a single space
			else
				std::cout << "  "; // don't print a number, but print two spaces

			--inner;
		}

		// A row has been printed, move to the next row
		std::cout << '\n';

		++outer;
	}

	return 0;
}