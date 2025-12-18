#include "PlayerHand.hpp"

namespace App
{
	namespace GameComponents
	{
		PlayerHand::PlayerHand(EventSystem::EventDispatcher& eventDispatcher, const Core::SDLBackend::Renderer& renderer, size_t numTiles, size_t numTilesPerRound)
			: m_highlighter(SDL_Color{ 0, 0, 255, 100 }, numTiles),
			  m_numTilesPerRound(numTilesPerRound),
			  mr_renderer(renderer),
			  mr_eventDispatcher(eventDispatcher),
			  m_numTiles(numTiles)
		{
			eventDispatcher.attach(*this);
		}

		void PlayerHand::render(Board& scrabbleBoard, const Core::SDLBackend::Renderer& renderer)
		{
			for (auto& tileReference : m_activeTiles)
			{
				std::unique_ptr<Tile>& tile = tileReference.get();

				if (tile->handlePress() == GameComponents::Tile::PressState::justReleased)
				{
					scrabbleBoard.addTileToBoard(tile.get());
				}
				else if (tile->handlePress() == GameComponents::Tile::PressState::pressed)
				{
					auto [w, h] = Utils::getWindowSize();
					const float numTiles = static_cast<float>(scrabbleBoard.getNumTiles());
					const float tileSize = h / static_cast<float>(numTiles);

					size_t tileIndex = scrabbleBoard.getSnapTileIndex({
						tile->pos.x + ((h / numTiles / 2.0f)),
						tile->pos.y + ((h / numTiles / 2.0f))
						});

					if (tileIndex != SIZE_MAX)
						m_highlighter.render(renderer, tileIndex);
				}

				tile->render(renderer);
			}
		}

		void PlayerHand::onInput(const bool* keyboardState, EventType e)
		{
			switch (e)
			{
			case EventType::roundStart:
				mr_eventDispatcher.reserveObserverVectorCapacity(m_numTilesPerRound);

				for (size_t i = 0; i <= m_numTilesPerRound; i++)
				{
					/*auto [beginIt, endIt] = mr_eventDispatcher.getObserverVectorIterators();
					size_t distance = std::distance(endIt - i, endIt);*/
					m_tiles.push_back(std::make_unique<Tile>(mr_renderer, m_numTiles));
					mr_eventDispatcher.attach(*m_tiles.back());
				}
				for (int i = 0; (i < 7) && (m_activeTiles.size() <= m_numTilesPerRound); i++)
				{
					m_activeTiles.push_back(m_tiles.at(i));
				}
				break;
			case EventType::gameEnd:
				for (auto& tile : m_tiles)
				{
					mr_eventDispatcher.dettach(*tile);
				}

				m_activeTiles.clear();
				m_tiles.clear();
			}
		}

		size_t PlayerHand::getNumTilesPerRound() const
		{
			return m_numTilesPerRound;
		}
	}
}