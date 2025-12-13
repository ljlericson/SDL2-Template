#include <random>

namespace Utils
{
	inline std::random_device randomDevice;

	int32_t getRandomInt(int32_t l, int32_t u);
}