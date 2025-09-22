// LEARNCPP_CHAP15.X_Q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <string_view>
#include "Random.h"

class Monster {
public:
	enum Type {
		dragon,
		goblin,
		ogre,
		orc,
		skeleton,
		troll,
		vampire,
		zombie,
		maxMonsterTypes,
	};

private:
	Type m_type{};
	std::string m_name{ "???" };
	std::string m_roar{ "???" };
	int m_hitPoints{};

public:
	Monster(Type type, std::string_view name, std::string_view roar, int hitPoints) :
		m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints } {
	}

	constexpr std::string_view getTypeString() const {
		switch (m_type) {
		case dragon:	return "dragon";
		case goblin:	return "goblin";
		case ogre:		return "ogre";
		case orc:		return "orc";
		case skeleton:	return "skeleton";
		case troll:		return "troll";
		case vampire:	return "vampire";
		case zombie:	return "zombie";
		default:		return "???";
		}
	}

	void print() const {
		if (m_hitPoints <= 0)
			std::cout << m_name << " the " << getTypeString() << " is dead.\n";
		else 
			std::cout << 
			m_name << " the " << getTypeString() << " has " << m_hitPoints << " hit points and says " << m_roar << ".\n";
	}
};

namespace MonsterGenerator {

	std::string_view static getName(int n) {
		switch (Random::get(0, 5)) {
		case 0: return "Blarg";
		case 1: return "Carg";
		case 2: return "Sarg";
		case 3: return "Klarg";
		case 4: return "Barg";
		case 5: return "Harg";
		default: return "???";
		}
	}

	std::string_view static getRoar(int n) {
		switch (Random::get(0, 5)) {
		case 0: return "*ROAR*";
		case 1: return "*SCREE*";
		case 2: return "*BAWK*";
		case 3: return "*MEOW*";
		case 4: return "*WOOF*";
		case 5: return "*HOOWWL*";
		default: return "???";
		}
	}

	Monster::Type static getType() {
		switch (Random::get(0, 7)) {
		case 0: return Monster::dragon;
		case 1: return Monster::goblin;
		case 2: return Monster::ogre;
		case 3: return Monster::orc;
		case 4: return Monster::skeleton;
		case 5: return Monster::troll;
		case 6: return Monster::vampire;
		case 7: return Monster::zombie;
		}
	}

	Monster static generate() {
		return Monster{getType(), getName(0), getRoar(0), Random::get(1, 100)};
	}
}

int main(){
	Monster m{ MonsterGenerator::generate() };
	m.print();
	return 0;	
}