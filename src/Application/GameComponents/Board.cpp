#include "Board.hpp"

namespace App
{
	namespace GameComponents
	{
		Board::Board(const Core::SDLBackend::Renderer& renderer, const Core::SDLBackend::Window& window)
		{
			m_tex = Core::AssetManager::textureManager->newTexture("Board", renderer.getRendHand(), "./assets/textures/board.png");
			auto [w, h] = Utils::getWindowSize();

			m_texRectShaking.h = static_cast<float>(h);
			m_texRectShaking.w = static_cast<float>(h);
			m_texRectShaking.x = 0.0f;
			m_texRectShaking.y = 0.0f;

			m_texRect = m_texRectShaking;
		}

		void Board::render(const Core::SDLBackend::Renderer& renderer)
		{
			auto [w, h] = Utils::getWindowSize();
			m_texRect.h = static_cast<float>(h);
			m_texRect.w = static_cast<float>(h);

			renderer.render(*m_tex, m_texRectShaking);
			m_texRectShaking = m_texRect;
		}
		
		void Board::onInput(const bool* keyboardState, EventType e)
		{
			if (keyboardState[SDL_SCANCODE_G])
				m_texRect.x += 1.0f;

			switch (e)
			{
			case EventType::screenShake:
				m_texRectShaking.x += Utils::getRandomInt(0, 10);
				m_texRectShaking.y += Utils::getRandomInt(0, 10);
				break;
			default:
				break;
			}

		}


		void Board::addTileToBoard(Tile* tile)
		{
			constexpr float snapMargin = 10.0f;

			const float minX = m_texRect.x;
			const float minY = m_texRect.y;
			const float maxX = m_texRect.x + m_texRect.w;
			const float maxY = m_texRect.y + m_texRect.h;

			// Reject if too far from board
			if (tile->pos.x < minX - snapMargin || tile->pos.x > maxX + snapMargin ||
				tile->pos.y < minY - snapMargin || tile->pos.y > maxY + snapMargin)
			{
				auto it = std::find(m_tiles.begin(), m_tiles.end(), tile);
				if (it != m_tiles.end())
					m_tiles.erase(it);

				tile->snapToTile(SIZE_MAX);
				return;
			}

			const float tileSize = m_texRect.w / static_cast<float>(m_numTiles);

			// Convert to board-local space
			const float localX = tile->pos.x - minX;
			const float localY = tile->pos.y - minY;

			// Tile index based on top-left corner
			const int tileX = static_cast<int>(std::floor(localX / tileSize));
			const int tileY = static_cast<int>(std::floor(localY / tileSize));

			const size_t index = static_cast<size_t>(tileY) * m_numTiles + tileX;

			// Validate indices
			if (tileX < 0 || tileX >= static_cast<int>(m_numTiles) ||
				tileY < 0 || tileY >= static_cast<int>(m_numTiles))
			{
				auto it = std::find(m_tiles.begin(), m_tiles.end(), tile);
				if (it != m_tiles.end())
					m_tiles.erase(it);

				tile->snapToTile(SIZE_MAX);
			}

			auto isOccupied = [&](int x, int y) -> bool
			{
				if (x < 0 || x >= static_cast<int>(m_numTiles) ||
					y < 0 || y >= static_cast<int>(m_numTiles))
					return false;

				for (const Tile* tile : m_tiles);
				{
					if (tile->getIndex() == y * m_numTiles + x)
						return true;
				}
				return false;
			};

			const bool hasAdjacent =
				isOccupied(tileX - 1, tileY) || // left
				isOccupied(tileX + 1, tileY) || // right
				isOccupied(tileX, tileY - 1) || // up
				isOccupied(tileX, tileY + 1);  // down

			// Allow placement if first tile or adjacent
			if (!hasAdjacent && index != (m_numTiles * m_numTiles - 1) / 2)
			{
				auto it = std::find(m_tiles.begin(), m_tiles.end(), tile);
				if (it != m_tiles.end())
					m_tiles.erase(it);

				tile->snapToTile(SIZE_MAX);
				return;
			}

			// success
			tile->snapToTile(index);
			m_tiles.push_back(tile);
		}

		size_t Board::getSnapTileIndex(glm::vec2 pos)
		{
			constexpr float snapMargin = 10.0f;

			const float minX = m_texRect.x;
			const float minY = m_texRect.y;
			const float maxX = m_texRect.x + m_texRect.w;
			const float maxY = m_texRect.y + m_texRect.h;

			// Reject if too far from board
			if (pos.x < minX - snapMargin || pos.x > maxX + snapMargin ||
				pos.y < minY - snapMargin || pos.y > maxY + snapMargin)
			{
				return SIZE_MAX;
			}

			const float tileSize = m_texRect.w / static_cast<float>(m_numTiles);

			// Convert to board-local space
			const float localX = pos.x - minX;
			const float localY = pos.y - minY;

			// Tile index based on top-left corner
			const int tileX = static_cast<int>(std::floor(localX / tileSize));
			const int tileY = static_cast<int>(std::floor(localY / tileSize));

			// Validate indices
			if (tileX < 0 || tileX >= static_cast<int>(m_numTiles) ||
				tileY < 0 || tileY >= static_cast<int>(m_numTiles))
			{
				return SIZE_MAX;
			}

			const size_t index = static_cast<size_t>(tileY) * m_numTiles + tileX;
			return index;
		}

		size_t Board::getNumTiles() const
		{
			return m_numTiles;
		}
	}
}