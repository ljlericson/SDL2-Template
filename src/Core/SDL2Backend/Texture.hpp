#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include <glm/glm.hpp>
#include <libpng16/png.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

namespace Core
{
	namespace SDLBackend
	{
		struct Texture
		{
			Texture() = default;
			Texture(SDL_Renderer* renderer, const std::string& fpath, glm::vec2 pos);
			~Texture();
			
			glm::vec2 pos = glm::vec3(0.0f);
			SDL_Texture* texHand = nullptr;
		};
	}
}