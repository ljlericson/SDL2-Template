#include "TileHighlighter.hpp"

namespace App
{
	namespace GameComponents
	{
		TileHighlighter::TileHighlighter(SDL_Color col, size_t numTiles)
			: m_col(col), m_numTiles(numTiles) 
		{		}

		void TileHighlighter::render(const Core::SDLBackend::Renderer& renderer, size_t index)
		{
            if (index >= m_numTiles * m_numTiles)
                return;

            auto [w, h] = Utils::getWindowSize();
            const float tileSize = h / static_cast<float>(m_numTiles);

            const size_t tileY = index / m_numTiles;
            const size_t tileX = index % m_numTiles;

            SDL_FRect rect;
            rect.x = tileX * tileSize;  // still top-left corner
            rect.y = tileY * tileSize;  // top-left corner
            rect.w = tileSize;
            rect.h = tileSize;

            renderer.render(rect, m_col, Core::SDLBackend::Renderer::DrawType::fill);
		}
	}
}