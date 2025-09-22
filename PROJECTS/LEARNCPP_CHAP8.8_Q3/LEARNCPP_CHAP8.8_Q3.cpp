// LEARNCPP_CHAP8.8_Q3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main(){
	int outer{ 5 };
	while (outer >= 1) {

		int inner{ outer };

		while(inner >= 1){
			std::cout << inner << ' ';
			--inner;
		}

		std::cout << '\n';
		--outer;
	}
	return 0;
}