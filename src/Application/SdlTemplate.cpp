#include "SdlTemplate.hpp"

namespace App
{
	Application::Application()
	{
        if (!SDL_Init(SDL_INIT_EVENTS))
            std::cerr << "SDL events failed to init, error: " << SDL_GetError() << '\n';

        if (!SDL_Init(SDL_INIT_VIDEO))
            std::cerr << "SDL video failed to init, error: " << SDL_GetError() << '\n';

		SDL_Log("SDL version: %d", SDL_GetVersion());
		
		m_window = std::make_unique<Core::SDLBackend::Window>("sdltemplate", 1280, 720);
		m_renderer = std::make_unique<Core::SDLBackend::Renderer>(*m_window);

		Utils::updateWindowSize(m_window->getWHand());

		m_scrabbleBoard = GameComponents::Board(*m_renderer, *m_window);
		m_eventDispatcher.attach(m_scrabbleBoard);

		m_highlighter = GameComponents::TileHighlighter(SDL_Color{ 0, 0, 255, 100 }, m_scrabbleBoard.getNumTiles());

		GameComponents::Tile tile1(*m_renderer, m_scrabbleBoard.getNumTiles());
		GameComponents::Tile tile2(*m_renderer, m_scrabbleBoard.getNumTiles());
		GameComponents::Tile tile3(*m_renderer, m_scrabbleBoard.getNumTiles());

		m_tiles.push_back(std::move(tile1));
		m_tiles.push_back(std::move(tile2));
		m_tiles.push_back(std::move(tile3));

		m_eventDispatcher.attach(m_tiles[0]);
		m_eventDispatcher.attach(m_tiles[1]);
		m_eventDispatcher.attach(m_tiles[2]);

		// imgui init
		/*IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsLight();*/
		//ImGui_ImplSDL3_InitForSDLRenderer(m_window->getWHand(), m_renderer->getRendHand());
	}

	void Application::run()
	{
		while (!m_window->shouldClose())
		{
			Utils::updateWindowSize(m_window->getWHand());

			m_window->pollEvents();
			m_renderer->preRender();

			m_scrabbleBoard.render(*m_renderer);

			for (auto& tile : m_tiles)
			{
				if (tile.handlePress() == GameComponents::Tile::PressState::justReleased)
				{
					m_scrabbleBoard.unCheckTile(tile.index);

					auto result = m_scrabbleBoard.snapTile(tile.pos);

					if (result)
					{
						auto [pos, tileIndex] = result.value();
						tile.pos = pos;
						tile.index = tileIndex;
						std::cout << "TILE SNAPPED TO INDEX: " << tileIndex << '\n';
					}
					else
					{
						switch (result.error())
						{
						case GameComponents::Board::SnapErrType::spotOccupied:
							std::cout << "TILE SPOT OCCUPIED\n";
							tile.pos = tile.getStartPos();
							break;
						case GameComponents::Board::SnapErrType::tooFarFromBoard:
							tile.pos = tile.getStartPos();
							break;
						}
					}
				}
				else if(tile.handlePress() == GameComponents::Tile::PressState::pressed)
				{
					auto [w, h] = Utils::getWindowSize();
					const float numTiles = static_cast<float>(m_scrabbleBoard.getNumTiles());
					const float tileSize = h / static_cast<float>(numTiles);

					size_t tileIndex = m_scrabbleBoard.getSnapTileIndex({ 
						tile.pos.x + ((h / static_cast<float>(numTiles) / 2.0f)),
						tile.pos.y + ((h / static_cast<float>(numTiles) / 2.0f))
					});

					if (tileIndex != SIZE_MAX)
						m_highlighter.render(*m_renderer, tileIndex);
				}

				tile.render(*m_renderer);
			}
			
			/*if (std::find(m_window->getUnhandledEvents().begin(), m_window->getUnhandledEvents().end(),
				SDL_EVENT_KEY_DOWN) != m_window->getUnhandledEvents().end())
				m_eventDispatcher.queueEvent(EventType::screenShake);*/


			m_renderer->postRender();
			m_eventDispatcher.poll();

			/*ImGui_ImplSDL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Test");
			ImGui::Text("This is a test");
			ImGui::End();

			ImGui::Render();
			ImGui_ImplSDL3_Render*/

			SDL_Delay(10);
		}
	}

	Application::~Application()
	{
		SDL_Quit();
	}
}