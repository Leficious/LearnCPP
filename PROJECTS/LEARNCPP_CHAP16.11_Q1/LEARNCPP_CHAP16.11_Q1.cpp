// LEARNCPP_CHAP16.11_Q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

template <typename T>
void push(std::vector<T>& arr, T num) {
    arr.push_back(num);
    static int pushCount{ 1 };
    std::cout << "Push " << pushCount << "\t(Stack:";
    if (static_cast<int>(arr.size()) <= 0) {
        std::cout << "empty)\n";
        return;
    }
    for (const auto& n : arr) {
        std::cout << ' ' << n;
    }
    std::cout << ")\n";
    ++pushCount;
}

template <typename T>
void pop(std::vector<T>& arr) {
    arr.pop_back();
    std::cout << "Pop\t" << "(Stack:";
    if (static_cast<int>(arr.size()) <= 0) {
        std::cout << "empty)\n";
        return;
    }
    for (const auto& n : arr) {
        std::cout << ' ' << n;
    }
    std::cout << ")\n";
}

int main()
{
    std::vector<int> stack{};
    std::cout << "\t(Stack: empty)\n";
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    pop<int>(stack);
    push(stack, 4);
    pop<int>(stack);
    pop<int>(stack);
    pop<int>(stack);
    return 0;
}

/*
       (Stack: empty)
Push 1 (Stack: 1)
Push 2 (Stack: 1 2)
Push 3 (Stack: 1 2 3)
Pop    (Stack: 1 2)
Push 4 (Stack: 1 2 4)
Pop    (Stack: 1 2)
Pop    (Stack: 1)
Pop    (Stack: empty)

*/
