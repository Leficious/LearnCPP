// LEARNCPP_CHAP16.6_Q3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <limits>

template <typename T>
auto getNum(T lo, T hi) {
	T out{};
	while (true) {
		std::cout << "Enter a number between " << lo << " and " << hi << ": ";
		if (std::cin >> out) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (out >= lo && out <= hi) return out;
	}
}

template <typename T>
void printArray(const std::vector<T>& arr) {
	for (std::size_t i{}; i < arr.size(); ++i) {
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}

template <typename T>
int findValue(const std::vector<T>& arr, T val) {
	for (std::size_t i{}; i < arr.size(); ++i) {
		if (val == arr[i]) return static_cast<int>(i);
	}
	return -1;
}


int main(){
	auto num{ getNum(1.0, 10.0) };
	// std::vector<int> arr{ 4, 6, 7, 3, 8, 2, 1, 9 };
	std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };
	printArray(arr);

	int matchIndex{ findValue(arr, num) };
	if (matchIndex >= 0) {
		std::cout << "The number " << num << " has index " << matchIndex << '\n';
	}
	else std::cout << "The number " << num << " was not found" << '\n';
	return 0;
}

/*

	Enter a number between 1 and 9: d
	Enter a number between 1 and 9: 6
	4 6 7 3 8 2 1 9
	The number 6 has index 1

	Enter a number between 1 and 9: 5
	4 6 7 3 8 2 1 9
	The number 5 was not found

*/
