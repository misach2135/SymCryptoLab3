#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "bigramutils.hpp"
#include "ciphrator.hpp"

std::vector<std::pair<std::string, utils::uintbox>> getMostFrequentBigrams(std::map<std::string, utils::uintbox> bigramsMap, uint64_t bigramsCount,double percent)
{
	double bound = percent * bigramsCount;
	std::vector<std::pair<std::string, utils::uintbox>> res;
	for (const auto& e : bigramsMap)
	{
		if (e.second.val >= bound)
		{
			res.push_back(e);
		}
	}

	std::sort(res.begin(), res.end(), [](std::pair<std::string, utils::uintbox> p1, std::pair<std::string, utils::uintbox> p2) {
		return p1.second > p2.second;
	});

	return res;
}

int main()
{
	using namespace utils;

	auto variantTextInfo = TextInfoFromFileWithoutSpaces("08.txt");
	auto naturalTextInfo = TextInfoFromFileWithoutSpaces("text.txt");

	auto vecVariant = getMostFrequentBigrams(variantTextInfo.nonOverlappingBigramsCount,variantTextInfo.nonOverlappingBigramsSize, 0.0065);
	auto vecNatural = getMostFrequentBigrams(naturalTextInfo.nonOverlappingBigramsCount, naturalTextInfo.nonOverlappingBigramsSize, 0.01);

	std::string bigram = "приветандрейнучтотикактичтоделал";

	auto temp = ciphrator::encrypt(bigram, 10, 5);

	std::cout << bigram << std::endl;
	std::cout << temp << std::endl;

	temp = ciphrator::decrypt(temp, 10, 5);

	std::cout << temp << std::endl;

	std::cout << std::endl;
	return 0;
}