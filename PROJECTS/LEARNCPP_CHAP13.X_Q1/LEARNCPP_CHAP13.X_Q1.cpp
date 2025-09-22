// LEARNCPP_CHAP13.X_Q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

enum class MonsterType{
    none,
    ogre,
    dragon,
    orc,
    giant,
    spider,
    slime,
};

struct Monster {
    MonsterType type{MonsterType::none};
    std::string name{};
    int health{};
};

std::ostream& operator<<(std::ostream& os, MonsterType& type) {
    switch (type) {
    case MonsterType::none: return os << "Invalid";
    case MonsterType::ogre: return os << "Ogre";
    case MonsterType::dragon: return os << "Dragon";
    case MonsterType::orc: return os << "orc";
    case MonsterType::giant: return os << "giant";
    case MonsterType::spider: return os << "spider";
    case MonsterType::slime: return os << "slime";
    default: return os << "Invalid";
    }
}

void printMonster(Monster& monster) {
    std::cout << "This " << monster.type << " is named " << monster.name << " and has " << monster.health << " health.\n";
}

int main(){
    Monster ogre { MonsterType::ogre, "Torg", 145 };
    Monster slime { MonsterType::slime, "Blurp", 23 };
    printMonster(ogre);
    printMonster(slime);
    return 0;
}
