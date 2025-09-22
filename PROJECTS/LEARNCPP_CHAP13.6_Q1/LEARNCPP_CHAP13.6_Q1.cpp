#include <iostream>

enum class Animal {
	pig,
	chicken,
	goat,
	cat,
	dog,
	duck,
};

constexpr std::string_view getAnimalName(Animal animal) {
	using enum Animal;
	switch (animal) {
	case pig:
		return "pig";
	case chicken:
		return "chicken";
	case goat:
		return "goat";
	case cat:
		return "cat";
	case dog:
		return "dog";
	case duck:
		return "duck";
	default:
		return "what kinda animals are you wrangling???";
	}
}

void printNumberOfLegs(Animal animal) {
	using enum Animal;
	switch (animal) {
	case pig:
	case goat:
	case cat:
	case dog:
		std::cout << "the " << getAnimalName(animal) <<  " has 4 legs\n";
		break;
	case chicken:
	case duck:
		std::cout << "the " << getAnimalName(animal) << " has 2 legs\n";
		break;
	default:
		std::cout << "what kinda animals are you wrangling???";
		break;
	}
}

int main() {
	printNumberOfLegs(Animal::cat);
	printNumberOfLegs(Animal::chicken);
	return 0;
}
