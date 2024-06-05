#include "mathutils.hpp"

using namespace utils;

int64_t utils::mod(int64_t a, int64_t n)
{
	if (a < 0)
	{
		a = -a * (n - 1);
	}
	return a % n;
}

utils::extendedGCDResult utils::extendedEuclid(int64_t a, int64_t n)
{
	int64_t u0 = 1;
	int64_t u1 = 0;
	int64_t u = 0;
	int64_t v0 = 0;
	int64_t v1 = 1;
	int64_t v = 0;
	int64_t r = 1;
	int64_t q = 0;

	while (r != 0)
	{
		q = a / n;
		r = a - q * n;
		u = u0 - q * u1;
		v = v0 - q * v1;

		a = n;
		n = r;
		u0 = u1;
		u1 = u;
		v0 = v1;
		v1 = v;
	}

	return extendedGCDResult(a, u0, v0);

}

int64_t utils::getInversed(int64_t a, int64_t n)
{
	auto res = extendedEuclid(a, n);
	if (res.gcd != 1) return 0;
	int64_t result = mod(res.u, n);
	return result;
}

std::list<int64_t> utils::solveEquation(int64_t a, int64_t b, int64_t n)
{
	std::list<int64_t> res;
	auto euclid = extendedEuclid(a, n);

	if (euclid.gcd == 1)
	{
		res.push_back(mod(euclid.u * b, n));
		return res;
	}

	if (mod(b, euclid.gcd)) return res;

	int64_t x0 = getInversed(a / euclid.gcd, n / euclid.gcd) * (b / euclid.gcd);
	int64_t n1 = n / euclid.gcd;

	for (int i = 0; i < euclid.gcd; i++)
	{
		res.push_back(mod(x0 + i * n1, n));
	}

	return res;
}