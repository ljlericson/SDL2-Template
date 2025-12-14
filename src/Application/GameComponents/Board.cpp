#include "Board.hpp"

namespace App
{
	namespace GameComponents
	{
		Board::Board(const Core::SDLBackend::Renderer& renderer, const Core::SDLBackend::Window& window)
		{
			m_occupiedTiles = std::make_unique<bool[]>(m_numTiles * m_numTiles);
			std::fill_n(m_occupiedTiles.get(), m_numTiles * m_numTiles, false);

			m_tex = Core::AssetManager::textureManager->newTexture("Board", renderer.getRendHand(), "./assets/textures/board2.png");
			auto [w, h] = Utils::getWindowSize();

			m_texRectShaking.h = static_cast<float>(h);
			m_texRectShaking.w = static_cast<float>(h);
			m_texRectShaking.x = 0.0f;
			m_texRectShaking.y = 0.0f;

			m_texRect = m_texRectShaking;
		}

		void Board::render(const Core::SDLBackend::Renderer& renderer) const
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

		auto Board::snapTile(glm::vec2 pos) -> std::expected<std::pair<glm::vec2, size_t>, SnapErrType>
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
				return std::unexpected(SnapErrType::tooFarFromBoard);
			}

			const float tileSize = m_texRect.w / static_cast<float>(m_numTiles);

			// Convert to board-local space
			const float localX = pos.x - minX;
			const float localY = pos.y - minY;

			// Nearest tile index (FIXED OFFSET BUG)
			const int tileX = static_cast<int>(
				std::floor((localX + tileSize * 0.5f) / tileSize)
				);
			const int tileY = static_cast<int>(
				std::floor((localY + tileSize * 0.5f) / tileSize)
				);

			// Validate indices
			if (tileX < 0 || tileX >= static_cast<int>(m_numTiles) ||
				tileY < 0 || tileY >= static_cast<int>(m_numTiles))
			{
				return std::unexpected(SnapErrType::tooFarFromBoard);
			}

			// Occupancy check
			const size_t index = static_cast<size_t>(tileY) * m_numTiles + tileX;
			if (m_occupiedTiles[index])
			{
				return std::unexpected(SnapErrType::spotOccupied);
			}

			// Snap to tile center
			const float snappedX = minX + tileX * tileSize;
			const float snappedY = minY + tileY * tileSize;

			m_occupiedTiles[index] = true;
			return std::pair{ glm::vec2(snappedX, snappedY), index };
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

		void Board::unCheckTile(size_t tile)
		{
			if(tile != SIZE_MAX)
				m_occupiedTiles[tile] = false;
		}

		size_t Board::getNumTiles() const
		{
			return m_numTiles;
		}
	}
}