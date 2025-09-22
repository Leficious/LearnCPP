// LEARNCPP_16.X_Q2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <string_view>

namespace Items {
    enum Item {
        healthPotion,
        torch,
        arrow,
        maxItem,
    };
}

int countItems(const std::vector<int>& arr) {
    int total{};
    for (const auto& n : arr) {
        total += n;
    }
    return total;
}

std::string_view printItemSingular(Items::Item item) {
    using namespace Items;
    switch (item) {
    case healthPotion:
        return "health potion";
    case torch:
        return "torch";
    case arrow:
        return "arrow";
    default:
        return "???";
    }
}

std::string_view printItemPlural(Items::Item item) {
    using namespace Items;
    switch (item) {
    case healthPotion:
        return "health potions";
    case torch:
        return "torches";
    case arrow:
        return "arrows";
    default:
        return "???";
    }
}

void printInventory(const std::vector<int>& arr) {
    int itemIndex{0};
    for (const auto& n : arr) {
        if (n == 0) std::cout << "You have no " << printItemPlural(Items::Item(itemIndex));
        else if (n == 1) std::cout << "You have 1 " << printItemSingular(Items::Item(itemIndex));
        else if (n > 1) std::cout << "You have " << n << ' ' << printItemPlural(Items::Item(itemIndex));
        std::cout << '\n';
        ++itemIndex;
    }
}

int main()
{
    std::vector inventory{ 1, 5, 10 };
    assert(inventory.size() == Items::maxItem);
    printInventory(inventory);
    std::cout << "You have a total of " << countItems(inventory) << " items\n";
    return 0;
}

/*
You have 1 health potion
You have 5 torches
You have 10 arrows
You have 16 total items
*/