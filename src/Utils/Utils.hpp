#pragma once
#include <random>

#include <SDL3/SDL.h>

namespace Utils
{
	inline std::random_device randomDevice;

	int32_t getRandomInt(int32_t l, int32_t u);

	std::pair<int, int> getWindowSize();

	void updateWindowSize(SDL_Window* window);
}