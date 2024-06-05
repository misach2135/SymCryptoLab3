#include "bigramutils.hpp"

#include <algorithm>

bool utils::isCharCyrrillic(char c)
{
	return (c >= (char)192) && (c <= (char)255);
}

double utils::CalcLetterEntropy(std::map<char, utils::uintbox> symbolsCount, uint64_t textSize)
{
	double res = 0.0;
	for (const auto& kv : symbolsCount)
	{
		double p = static_cast<double>(kv.second.val) / textSize;
		res -= p * log2(p);
	}
	return res;
}

double utils::CalcOverlappingBigramEntropy(std::map<std::string, utils::uintbox> overlappingBigramsCount, uint64_t textSize)
{
	double res = 0.0;
	for (const auto& kv : overlappingBigramsCount)
	{
		double p = static_cast<double>(kv.second.val) / (textSize - 1);
		res -= p * log2(p);
	}
	return res / 2;
}

double utils::CalcNonOverlappingBigramEntropy(std::map<std::string, utils::uintbox> nonOverlappingBigramsCount, uint64_t textSize)
{
	double res = 0.0;
	for (const auto& kv : nonOverlappingBigramsCount)
	{
		double p = static_cast<double>(kv.second.val) / (textSize / 2);
		res -= p * log2(p);
	}
	return res / 2;
}

utils::TextInfo utils::TextInfoFromFileWithoutSpaces(std::string filename)
{
	std::setlocale(LC_ALL, "ru-Ru");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::ifstream in(filename);

	TextInfo info;
	info.textSize = 0;

	if (in.is_open())
	{
		std::cout << "Filter input text..." << std::endl;

		std::stringstream ss;
		in >> std::skipws;
		char prev = 0;
		char c = 0;
		while (in.get(c))
		{
			if ((isCharCyrrillic(c) && !isspace(c) && (c != 10)))
			{
				c = tolower(c);
				ss << c;
				// std::cout << c;
				prev = c;
			}
		}
		std::cout << std::endl;
		std::cout << "Starting counting symbols..." << std::endl;

		c = 0;
		ss >> std::skipws;

		while (ss.get(c))
		{
			info.symbolsCount[c].val++;
			char next = ss.peek();
			if (!ss.eof())
			{
				std::string bigram{ c, next };

				info.overlappingBigramsCount[bigram].val++;
				info.overlappingBigramsSize++;

				if (info.textSize % 2 == 0)
				{
					info.nonOverlappingBigramsCount[bigram].val++;
					info.nonOverlappingBigramsSize++;
				}
			}
			info.textSize++;
		}

	}
	else
	{
		std::cout << "Could not open input file." << std::endl;
		return TextInfo{};
	}
	in.close();

	std::cout << "Calculating entropy..." << std::endl;

	info.symbolsEntropy = CalcLetterEntropy(info.symbolsCount, info.textSize);
	info.nonOverlappingBigramsEntropy = CalcNonOverlappingBigramEntropy(info.nonOverlappingBigramsCount, info.textSize);
	info.overlappingBigramsEntropy = CalcOverlappingBigramEntropy(info.overlappingBigramsCount, info.textSize);

	std::cout << "Done!" << std::endl;

	return info;
}

utils::TextInfo utils::TextInfoFromStringWithoutSpaces(const std::string& text)
{
	utils::TextInfo info;
	info.textSize = 0;
	std::stringstream ss(text);
	char c = 0;
	ss >> std::skipws;

	while (ss.get(c))
	{
		info.symbolsCount[c].val++;
		char next = ss.peek();
		if (!ss.eof())
		{
			std::string bigram{ c, next };

			info.overlappingBigramsCount[bigram].val++;
			info.overlappingBigramsSize++;

			if (info.textSize % 2 == 0)
			{
				info.nonOverlappingBigramsCount[bigram].val++;
				info.nonOverlappingBigramsSize++;
			}
		}
		info.textSize++;
	}

	info.symbolsEntropy = CalcLetterEntropy(info.symbolsCount, info.textSize);
	info.nonOverlappingBigramsEntropy = CalcNonOverlappingBigramEntropy(info.nonOverlappingBigramsCount, info.textSize);
	info.overlappingBigramsEntropy = CalcOverlappingBigramEntropy(info.overlappingBigramsCount, info.textSize);


	return info;
}

std::string utils::ParseText(const std::string& filename)
{
	std::setlocale(LC_ALL, "ru-Ru");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::ifstream in(filename);

	if (!in.is_open()) return "";

	std::stringstream ss;
	in >> std::skipws;
	char c = 0;
	while (in.get(c))
	{
		if ((isCharCyrrillic(c) && !isspace(c) && (c != 10)))
		{
			c = tolower(c);
			ss << c;
			// std::cout << c;
		}
	}

	return ss.str();

}

std::vector<std::pair<std::string, utils::uintbox>> utils::getMostFrequentBigrams(std::map<std::string, utils::uintbox> bigramsMap, int count)
{
	std::vector<std::pair<std::string, utils::uintbox>> res;
	for (const auto& e : bigramsMap)
	{
		res.push_back(e);
	}

	std::sort(res.begin(), res.end(), [](std::pair<std::string, utils::uintbox> p1, std::pair<std::string, utils::uintbox> p2) {
		return p1.second > p2.second;
		});

	if (count > res.size()) throw new std::exception("Too large count!");
	res.erase(res.begin() + count, res.end());

	return res;
}

bool utils::checkBigramCorrectness(const std::string& bigram)
{
	if (bigram.size() != 2) return false;
	//auto check = [](char c) {return (c >= (char)224) && (c <= (char)255); };
	auto check = [](char c) {
		auto res = std::find(alphabet.begin(), alphabet.end(), c);
		return (res - alphabet.begin()) < alphabet.size();
		};
	return check(bigram[0]) && check(bigram[1]);
}

int32_t utils::bigramToNum(const std::string& bigram)
{
	if (!checkBigramCorrectness(bigram))
	{
		throw new std::exception("Bigram not correct!");
		return -1;
	}
	int32_t res = 0;
	auto x0Iter = std::find(alphabet.begin(), alphabet.end(), bigram[0]);
	auto x1Iter = std::find(alphabet.begin(), alphabet.end(), bigram[1]);
	int32_t x0 = x0Iter - alphabet.begin();
	int32_t x1 = x1Iter - alphabet.begin();

	return x0 * M + x1;
}

std::string utils::numToBigram(int32_t bigramNum)
{
	if ((0 > bigramNum) || (bigramNum > 31 * 31))
	{
		throw new std::exception("Bigram number is not correct!");
		return "";
	}

	char x0 = alphabet[bigramNum / M];
	char x1 = alphabet[bigramNum % M];

	return std::string({ x0, x1 });
}
