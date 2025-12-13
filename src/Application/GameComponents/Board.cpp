#include "Board.hpp"

namespace App
{
	namespace GameComponents
	{
		Board::Board(const Core::SDLBackend::Renderer& renderer)
		{
			m_tex = Core::AssetManager::textureManager->newTexture("Board", renderer.getRendHand(), "./assets/textures/board.png");
			m_texRect.h = 500.0f;
			m_texRect.w = 500.0f;
			m_texRect.x = 0.0f;
			m_texRect.y = 0.0f;

			m_texRectOriginal = m_texRect;
		}

		void Board::render(const Core::SDLBackend::Renderer& renderer) const
		{
			renderer.render(*m_tex, m_texRect);
			m_texRect = m_texRectOriginal;
		}

		void Board::onInput(const bool* keyboardState, EventType e)
		{
			if (keyboardState[SDL_SCANCODE_G])
				m_texRect.x += 1.0f;

			switch (e)
			{
			case EventType::screenShake:
				m_texRect.x += Utils::getRandomInt(0, 10);
				m_texRect.y += Utils::getRandomInt(0, 10);
				break;
			default:
				break;
			}

		}
	}
}