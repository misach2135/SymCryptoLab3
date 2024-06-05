#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "bigramutils.hpp"
#include "ciphrator.hpp"

int main()
{
	using namespace utils;

	std::string text = ParseText("08.txt");
	std::string textNatural = ParseText("text3.txt");
	std::ofstream out("out.txt");

	auto textInfo = TextInfoFromFileWithoutSpaces("text1.txt");
	auto mostFrequentBigrams = getMostFrequentBigrams(textInfo.nonOverlappingBigramsCount, 5);

	std::vector<std::string> bigrams;

	for (int i = 0; i < mostFrequentBigrams.size(); i++)
	{
		bigrams.push_back(mostFrequentBigrams[i].first);
	}

	//std::cout << ciphrator::decrypt(text, 558, 586) << std::endl;

	auto temp = ciphrator::decrypt(ciphrator::encrypt(textNatural, 60, 1), 60, 1);

	ciphrator::hack(text, {"ст", "но", "то", "на", "ен"}, out);
	//std::cout << ciphrator::isNaturalLang(textNatural, 0.3) << std::endl;

	std::cout << std::endl;
	return 0;
}