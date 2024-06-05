#ifndef CIPHRATOR_HPP
#define CIPHRATOR_HPP

#include <string>
#include <vector>

#include "mathutils.hpp"
#include "bigramutils.hpp"

namespace ciphrator
{
	std::string encrypt(const std::string& text, int32_t a, int32_t b);
	std::string decrypt(const std::string& text, int32_t a, int32_t b);
	std::string hack(const std::string& text, std::vector<std::string> naturalBigrams);
}

#endif