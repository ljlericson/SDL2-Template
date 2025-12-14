#pragma once
#include <iostream>
#include <memory>

#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <imgui.h>
//#include <imgui_impl_sdl3.h>

#include "../Core/AssetManager/TextureManager.hpp"
#include "../Core/SDL2Backend/Window.hpp"
#include "../Core/SDL2Backend/Texture.hpp"
#include "../Core/SDL2Backend/Renderer.hpp"
#include "EventSystem/EventDispatcher.hpp"

#include "GameComponents/Board.hpp"
#include "GameComponents/Tile.hpp"
#include "GameComponents/TileHighlighter.hpp"

#include "../Utils/Utils.hpp"


namespace App
{
	class Application
	{
	public:
		Application();
		void run();
		~Application();

	private:
		std::unique_ptr<Core::SDLBackend::Window> m_window;
		std::unique_ptr<Core::SDLBackend::Renderer> m_renderer;
		EventSystem::EventDispatcher m_eventDispatcher;

		GameComponents::Board m_scrabbleBoard;
		GameComponents::TileHighlighter m_highlighter;
		std::vector<GameComponents::Tile> m_tiles;
	};
}