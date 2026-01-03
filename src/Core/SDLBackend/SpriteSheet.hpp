#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "Texture.hpp"
#include "Renderer.hpp"

#include "../AssetManager/AssetManager.hpp"

namespace Core
{
	namespace SDLBackend
	{
		class SpriteSheet
		{
		public:
			SpriteSheet() = default;
			SpriteSheet(SDL_Renderer* renderer, const std::string& fpath, int frameW, int frameH, int numFramesX, int numFramesY);
			SpriteSheet(SDL_Texture* texture, int frameW, int frameH, int numFramesX, int numFramesY);
			~SpriteSheet() = default;

			void render(const Renderer& renderer);

			void setFrame(int frame);

		public:
			glm::vec2 pos;
		private:
			std::shared_ptr<Texture> m_texHand;
			SDL_FRect m_texRect, m_srcRect;
			const int m_frameW, m_frameH, m_numFramesX, m_numFramesY;
			int m_currentFrame = 0;
		};
	}
}