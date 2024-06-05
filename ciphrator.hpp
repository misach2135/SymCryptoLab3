#ifndef CIPHRATOR_HPP
#define CIPHRATOR_HPP

#include <string>
#include <vector>

#include "mathutils.hpp"
#include "bigramutils.hpp"

namespace ciphrator
{
	const double H1Entropy = 4.45052;
	const double H2OverlappingEntropy = 4.02623;
	const double H2NonOverlappingEntropy = 3.96798;

	bool isNaturalLang(const std::string& text, double epsilon);

	std::string encrypt(const std::string& text, int32_t a, int32_t b);
	std::string decrypt(const std::string& text, int32_t a, int32_t b);
	void hack(const std::string& text, std::vector<std::string> naturalBigrams, std::ofstream& out);
}

#endif