#include "Tile.hpp"

namespace App
{
	namespace GameComponents
	{
		Tile::Tile(const Core::SDLBackend::Renderer& renderer, size_t numTiles)
			: pos(0.0f), m_numTilesOnBoard(numTiles), m_char("")
		{
			sm_numTiles++;


			if(!sm_font)
				sm_font = TTF_OpenFont("./assets/font.ttf", 32);

			m_tex = Core::AssetManager::textureManager->newTexture("Tile", renderer.getRendHand(), "./assets/textures/test.jpg");

			auto [w, h] = Utils::getWindowSize();
			m_texRect.h = h / static_cast<float>(numTiles);
			m_texRect.w = h / static_cast<float>(numTiles);
			pos.x = static_cast<float>(w) - m_texRect.w - (sm_numTiles * m_texRect.w);
			pos.y = static_cast<float>(h) - m_texRect.h - 50.0f;

			//const char* character = const_cast<char*>(&m_char);
			m_char = { char('A' + Utils::getRandomInt(0, 24)) };

			m_startPos = pos;
		}

		void Tile::render(const Core::SDLBackend::Renderer& renderer)
		{
			m_texRect.x = pos.x;
			m_texRect.y = pos.y;
			if(!m_textTexture.texHand)
			{
				SDL_Surface* textSurface = TTF_RenderText_Solid(sm_font, m_char.c_str(), m_char.length(), SDL_Color(255, 0, 0, 255));
				if (!textSurface)
					std::cout << "TEXT ERR: " << SDL_GetError() << '\n';
				m_textTexture = std::move(Core::SDLBackend::Texture(SDL_CreateTextureFromSurface(renderer.getRendHand(), textSurface)));
				SDL_DestroySurface(textSurface);
			}

			renderer.render(*m_tex, m_texRect);
			renderer.render(m_textTexture, m_texRect);
		}

		void Tile::glideToStartPos()
		{
			sm_numTiles++;
			m_glidingToStart = true;
		}

		void Tile::snapToTile(size_t index)
		{
			sm_numTiles--;
			m_index = index;

			if (m_index == SIZE_MAX)
			{
				std::cout << "FAILED\n";
				this->glideToStartPos();
				return;
			}

			auto [w, h] = Utils::getWindowSize();
			const float tileSize = h / static_cast<float>(m_numTilesOnBoard);

			const size_t tileY = m_index / m_numTilesOnBoard;
			const size_t tileX = m_index % m_numTilesOnBoard;

			pos.x = tileX * tileSize;
			pos.y = tileY * tileSize;
		}

		void Tile::onInput(const bool* keyboardState, EventType e)
		{
			m_ctrPressed = keyboardState[SDL_SCANCODE_LCTRL];

			switch (e)
			{
			case EventType::screenShake:
				std::cout << "SHAKING\n";
				break;
			default:
				break;
			}

			if (m_glidingToStart && pos != m_startPos)
			{
				pos.x += (getStartPos().x - pos.x) / 10.0f;
				pos.y += (getStartPos().y - pos.y) / 10.0f;
			}
			if(glm::distance(pos, m_startPos) < 10.0f)
			{
				pos = m_startPos;
				m_glidingToStart = false;
			}
		}

		Tile::PressState Tile::handlePress()
		{
			const float minX = pos.x;
			const float minY = pos.y;
			const float maxX = pos.x + m_texRect.w;
			const float maxY = pos.y + m_texRect.h;

			float mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			// I honestly have no clue how this if
			// statement got this complex
			if (
					// check that another tile isnt engaged and that control is pressed
				   (((m_ctrPressed) && (!sm_tilePressEngaged) && (!m_tilePressed)) ||
				   (((m_ctrPressed) && (sm_tilePressEngaged) && (m_tilePressed))))

										&&
					// check that the mouse curser is over the tile
					     (((mouseX > minX && mouseX < maxX) &&
					       (mouseY > minY && mouseY < maxY))     
						  || m_tilePressed) // or the tile is already pressed (bug fix)
				)
			{
				pos.x = mouseX - (m_texRect.w / 2.0f);
				pos.y = mouseY - (m_texRect.h / 2.0f);

				m_tilePressed = true;
				sm_tilePressEngaged = true;
				return PressState::pressed;
			}
			// control not pressed and tile engaged means
			// user has just released tile
			else if (!m_ctrPressed && m_tilePressed)
			{
				m_tilePressed = false;
				sm_tilePressEngaged = false;
				pos.x = mouseX - (m_texRect.w / 2.0f);
				pos.y = mouseY - (m_texRect.h / 2.0f);
				return PressState::justReleased;
			}

			// else tile isnt engaged
			return PressState::notPressed;
		}

		glm::vec2 Tile::getStartPos() const
		{
			return m_startPos;
		}

		size_t Tile::getIndex() const
		{
			return m_index;
		}
	}
}