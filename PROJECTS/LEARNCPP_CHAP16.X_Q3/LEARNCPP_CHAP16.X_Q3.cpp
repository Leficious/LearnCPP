// LEARNCPP_CHAP16.X_Q3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <utility>

template <typename T>
std::pair<T, T> getMinMax(std::vector<T>& arr) {
    T min{arr[0]};
    T max{arr[0]};
    for (const auto& n : arr) {
        if (n < min) min = n;
        if (n > max) max = n;
    }
    return { min, max };
}

template <typename T>
void printMinMax(std::vector<T>& arr) {
    std::pair<T, T> minMax{ getMinMax(arr) };
    std::size_t minIndex{};
    std::size_t maxIndex{};

    std::cout << "With array ( ";
    std::size_t itemIndex{ 0 };
    for (const auto& n : arr) {
        if (itemIndex == (std::size(arr) - 1)) std::cout << n << " ):\n";
        else std::cout << n << ", ";
        if (n == minMax.first) minIndex = itemIndex;
        if (n == minMax.second) maxIndex = itemIndex;
        ++itemIndex;
    }

    std::cout << "The min element has index " << minIndex << " and value " << minMax.first << '\n';
    std::cout << "The max element has index " << maxIndex << " and value " << minMax.second << "\n\n";
}

int main(){
    /*std::vector v1{3, 8, 2, 5, 7, 8, 3};
    std::vector v2{ 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
    printMinMax(v1);
    printMinMax(v2);*/

    std::cout << "Enter numbers to add (use -1 to stop): ";
    std::vector<int> v3{};
    int n{};
    std::cin >> n;
    if (n == -1) std::cout << "Your array is empty\n";
    else {
        v3.push_back(n);
        while (n != -1) {
            std::cin >> n;
            if (n != -1) v3.push_back(n);
        }
        printMinMax(v3);
    }
    return 0;
}

/*

Enter numbers to add (use -1 to stop): 3 8 5 2 3 7 -1
With array ( 3, 8, 5, 2, 3, 7 ):
The min element has index 3 and value 2
The max element has index 1 and value 8

With array ( 3, 8, 2, 5, 7, 8, 3 ):
The min element has index 2 and value 2
The max element has index 1 and value 8

With array ( 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 ):
The min element has index 4 and value 1.2
The max element has index 5 and value 8.8

*/
