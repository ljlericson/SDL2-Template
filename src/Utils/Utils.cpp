#include "Utils.hpp"

namespace Utils
{
	static int s_w = 0, s_h = 0;

	int32_t getRandomInt(int32_t l, int32_t u)
	{
		std::uniform_int_distribution<> dist(l, u);

		return dist(randomDevice);
	}

	std::pair<int, int> getWindowSize()
	{
		return { s_w, s_h };
	}

	template<typename T> requires std::is_integral_v<T>
	size_t getNumDigits(T val)
	{
		if (val == 0)
		{
			return 1;
		}

		if constexpr (std::is_signed_v<T>) 
		{
			val = static_cast<T>(std::abs(val));
		}

		size_t count = 0;
		while (val != 0)
		{
			val = val / 10;
			count++;
		}
		return count;
	}

	void updateWindowSize(SDL_Window* window)
	{
		SDL_GetWindowSize(window, &s_w, &s_h);
	}

	//template size_t getNumDigits<size_t>(size_t);
	//template size_t getNumDigits<int>(int);
	//template size_t getNumDigits<uint32_t>(uint32_t);
}