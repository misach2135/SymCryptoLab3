#ifndef BIGRAM_UTILS_HPP
#define BIGRAM_UTILS_HPP

#include <cstdint>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <array>
#include <Windows.h>
#include <sstream>


namespace utils
{
	// Code taken from lab-1, without any changes

	struct uintbox
	{
		uint64_t val = 0;
		operator uint64_t() { return val; }
	};

	struct TextInfo
	{
		uint32_t textSize = 0;
		uint32_t overlappingBigramsSize = 0;
		uint32_t nonOverlappingBigramsSize = 0;
		std::map<char, uintbox> symbolsCount;
		std::map<std::string, uintbox> overlappingBigramsCount;
		std::map<std::string, uintbox> nonOverlappingBigramsCount;

		double symbolsEntropy = 0;
		double overlappingBigramsEntropy = 0;
		double nonOverlappingBigramsEntropy = 0;

	};

	bool isCharCyrrillic(char c);

	double CalcLetterEntropy(std::map<char, uintbox> symbolsCount, uint64_t textSize);

	double CalcOverlappingBigramEntropy(std::map<std::string, uintbox> overlappingBigramsCount, uint64_t textSize);

	double CalcNonOverlappingBigramEntropy(std::map<std::string, uintbox> nonOverlappingBigramsCount, uint64_t textSize);

	TextInfo TextInfoFromFileWithoutSpaces(std::string filename);

	// And from now completly new code)

	const int32_t M = 31;
	const std::array<char, 31> alphabet = { 'а','б','в','г','д','е','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ы','ь','э','ю','я' };

	bool checkBigramCorrectness(const std::string& bigram);
	int32_t bigramToNum(const std::string& bigram);
	std::string numToBigram(int32_t bigramNum);

}


#endif