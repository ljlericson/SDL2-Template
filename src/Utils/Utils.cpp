#include "Utils.hpp"

namespace Utils
{
	int32_t getRandomInt(int32_t l, int32_t u)
	{
		std::uniform_int_distribution<> dist(l, u);

		return dist(randomDevice);
	}
}