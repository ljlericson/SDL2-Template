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

	void updateWindowSize(SDL_Window* window)
	{
		SDL_GetWindowSize(window, &s_w, &s_h);
	}
}