#pragma once

#include <SDL3/SDL.h>
#include "../../Core/SDLBackend/Renderer.hpp"
#include "../../Utils/Utils.hpp"


namespace App
{
	namespace GameComponents
	{
		class TileHighlighter
		{
		public:
			TileHighlighter() = default;
			TileHighlighter(SDL_Color col, size_t numTiles);

			void render(const Core::SDLBackend::Renderer& renderer, size_t index);

		private:
			SDL_Color m_col = { 0, 0, 0, 0 };
			size_t m_numTiles = 0;
		};
	}
}