#ifndef MATHUTILS_LAB3_HPP
#define MATHUTILS_LAB3_HPP

#include <cstdint>
#include <tuple>
#include <list>

namespace utils
{
	struct extendedGCDResult
	{
		int64_t gcd = 0;
		int64_t u = 0;
		int64_t v = 0;

		extendedGCDResult(int64_t gcd, int64_t u, int64_t v) : gcd(gcd), u(u), v(v) {}
	};

	int64_t mod(int64_t a, int64_t n);
	extendedGCDResult extendedEuclid(int64_t a, int64_t n);           // apply extended euclid on (a, n) and returns gcd, and u,v s.t au + vn = gcd
	int64_t getInversed(int64_t a, int64_t n);                        // better to use it for get a^-1
	std::list<int64_t> solveEquation(int64_t a, int64_t b, int64_t n);
}

#endif