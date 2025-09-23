#include <iostream>
#include <string_view>
#include <vector>
#include "Random.h"

namespace Settings {
	constexpr int wrongGuessesAllowed{ 6 };
}

namespace WordList {
	std::vector<std::string_view> list
	{ "mystery", "broccoli", "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };
	
	std::string_view pickWord() {
		return list[Random::get<std::size_t>(0, (list.size() - 1))];
	}
}

class Session {
private:
	std::string_view targetWord{ WordList::pickWord() };
	std::vector<char> guessedChars{};
	int wrongGuessesLeft{ Settings::wrongGuessesAllowed };
public:
	constexpr std::string_view getTargetWord() const { return targetWord; }
	constexpr std::vector<char> getGuessedChars() const { return guessedChars; }
	constexpr int getWrongGuessesLeft() const { return wrongGuessesLeft; }
	void addGuessedChar(char c) { guessedChars.push_back(c); }
	void subtractGuess() { --wrongGuessesLeft; }

	bool isLetterInWord(char c) const {
		for (const auto& n : targetWord) {
			if (n == c) return true;
		}
		return false;
	}
	bool isLetterGuessed(char c) const {
		for (const auto& n : guessedChars) {
			if (n == c) return true;
		}
		return false;
	}
	bool isWon() {
		for (const auto& c : targetWord) {
			if (!isLetterGuessed(c)) return false;
		}
		return true;
	}
};

void displaySession(const Session& s) {
	std::cout << "\nThe word: ";
	for (const auto& c : s.getTargetWord()) {
		if (s.isLetterGuessed(c)) std::cout << c;
		else std::cout << '_';
	}
	std::cout << "\tWrong guesses: ";
	for (int i{ 0 }; i < s.getWrongGuessesLeft(); ++i) {
		std::cout << '+';
	}
	for (char c = 'a'; c <= 'z'; ++c) {
		if (s.isLetterGuessed(c) && !s.isLetterInWord(c))
			std::cout << c;
	}
	std::cout << '\n';
}

char getChar(Session& s) {
	char c{};
	while (true) {
		std::cout << "Enter your next letter: ";
		std::cin >> c;
		if (!std::cin) {
			std::cin.clear();
			std::cout << "That wasn't a valid input. Try again.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (c < 'a' || c > 'z') {
			std::cout << "That wasn't a valid input. Try again.\n";
			continue;
		}
		if (s.isLetterGuessed(c)) {
			std::cout << "You already guessed that. Try again.\n";
			continue;
		}
		return c;
	}
}

void handleGuess(Session& s, char c) {
	s.addGuessedChar(c);
	if (s.isLetterInWord(c)) {
		std::cout << "Yes, " << c << " is in the word!\n";
		return;
	}
	std::cout << "No, " << c << " is not in the word\n";
	s.subtractGuess();
}

int main() {
	std::cout << "Welcome to C++man (a variant of Hangman)\nTo win: guess the word. To lose: run out of pluses.\n";
	Session s{};
	while (s.getWrongGuessesLeft() && !s.isWon()) {
		displaySession(s);
		char c{ getChar(s) };
		handleGuess(s, c);
	}
	displaySession(s);
	if (!s.getWrongGuessesLeft())
		std::cout << "You lost! The word was: " << s.getTargetWord() << '\n';
	else std::cout << "You won!\n";
	return 0;
}
