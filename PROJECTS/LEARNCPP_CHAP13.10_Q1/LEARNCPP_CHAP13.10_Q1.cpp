// LEARNCPP_CHAP13.10_Q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
struct SiteData {
	int adsWatched{};
	float percentClicked{};
	float earnPerClick{};
};

void printSiteData(const SiteData& data) {
	std::cout << "ads watched: " << data.adsWatched << '\n';
	std::cout << "percent clicked: " << data.percentClicked << '\n';
	std::cout << "earnings per click: " << data.earnPerClick << '\n';
	std::cout << "total earnings: " << (data.adsWatched * (data.percentClicked/100) * data.earnPerClick) << '\n';
}

SiteData inputData() {
	std::cout << "input how many ads were watched: ";
	int adsWatched{};
	std::cin >> adsWatched;

	std::cout << "input the percentage of clicks: ";
	float percentClicked{};
	std::cin >> percentClicked;

	std::cout << "input earnings per click: ";
	float earnPerClick{};
	std::cin >> earnPerClick;

	return { adsWatched, percentClicked, earnPerClick };
}

int main() {
	printSiteData(inputData());
	return 0;
}
