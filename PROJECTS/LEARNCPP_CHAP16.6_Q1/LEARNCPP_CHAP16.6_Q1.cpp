#include <iostream>
#include <vector>

template <typename T>
void printArray(const std::vector<T>& arr) {
    for (int i{ 0 }; i < static_cast<int>(arr.size()); ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printArray(arr); // use function template to print array

    return 0;
}

/** 4 6 7 3 8 2 1 9 */