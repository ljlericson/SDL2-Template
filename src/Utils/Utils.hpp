#pragma once
#include <type_traits>
#include <random>

#include <SDL3/SDL.h>

namespace Utils
{
	inline std::random_device randomDevice;

	int32_t getRandomInt(int32_t l, int32_t u);

	std::pair<int, int> getWindowSize();

	template<typename T> requires std::is_integral_v<T>
	size_t getNumDigits(T val);

	void updateWindowSize(SDL_Window* window);
}