// LEARNCPP_8.X_Q3_HI-LO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Random.h"
#include <limits>

void ignoreLine() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool hiLow(int val, int target) {
	if (val > target) {
		std::cout << "Your guess is too high.\n";
		return false;
	}
	else if (val < target) {
		std::cout << "Your guess is too low.\n";
		return false;
	}
	else return true;
}

// asks user for input + checks whether the input is the correct type
int getInt() {
	int x{};
	while (true) {
		std::cin >> x;
		if (!std::cin) {
			std::cin.clear();
			ignoreLine();
			std::cout << "Invalid input. Please enter an integer: ";
			continue;
		}
		ignoreLine();
		return x;
	}
}

void gameStart(int numGuesses, int min, int max) {
	const int targetVal{ Random::get(min, max) };
	std::cout << "Let's play a game. I'm thinking of a number between " << min << " and " << max << ". You have " << numGuesses << " tries to guess what it is.\n";

	for (int i{ 1 }; i <= numGuesses; ++i) {
		std::cout << "Guess #" << i << ": ";
		int guessedVal{ getInt() };
		if (guessedVal > max || guessedVal < min) std::cout << "Remember, the number is between " << min << " and " << max << ".\n";
		if (hiLow(guessedVal, targetVal)) {
			std::cout << "Correct! You win!\n";
			return;
		}
	}
	std::cout << "Sorry, you lose. The correct number was " << targetVal << ".\n";
}

// prompts user for y/n propmt. loops if given invalid input
bool playAgain() {
	while (true) {
		std::cout << "Would you like to play again (y / n)?: ";
		char ch{};
		std::cin >> ch;
		ignoreLine();
		switch (ch) {
		case 'y': case 'Y': return true;
		case 'n': case 'N': return false;
		default: std::cout << "Invalid input. Please input y or n.\n";
		}
	}
}

int main() {
	int numGuesses{ 7 };
	int min{ 1 };
	int max{ 100 };
	do {
		gameStart(numGuesses, min, max);
	} while (playAgain());
	std::cout << "Thank you for playing.\n";
	return 0;
}

