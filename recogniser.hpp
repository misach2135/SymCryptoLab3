#ifndef RECOGNISER_HPP
#define RECOGNISER_HPP

#include <string>

// despite the english naming, its russian recogniser)
namespace recogniser
{
	const double H1Entropy = 4.45052;
	const double H2OverlappingEntropy = 4.02623;
	const double H2NonOverlappingEntropy = 3.96798;

	// TODO!
	bool isNaturalLang(const std::string& text);

}

#endif