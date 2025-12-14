#pragma once

#include <SDL3/SDL.h>

#include "BasicGameComponent.hpp"
#include "../../Core/AssetManager/AssetManager.hpp"
#include "../../Core/SDL2Backend/Renderer.hpp"
#include "../../Core/SDL2Backend/Texture.hpp"
#include "../../Utils/Utils.hpp"

namespace App
{
	namespace GameComponents
	{
		class Tile : public BasicGameComponent
		{
		public:
			enum class PressState
			{
				notPressed,
				justReleased,
				pressed
			};

			Tile() = default;

			Tile(const Core::SDLBackend::Renderer& renderer, size_t numTiles);

			void render(const Core::SDLBackend::Renderer& renderer) const override;

			void onInput(const bool* keyboardState, EventType e) override;

			PressState handlePress();

			glm::vec2 getStartPos();

			~Tile();

		public:
			glm::vec2 pos;
			size_t index = SIZE_MAX;
		private:
			Core::SDLBackend::Texture* m_tex;
			mutable SDL_FRect m_texRect;
			glm::vec2 m_startPos;
			bool m_ctrPressed = false;
			bool m_tilePressed = false;
			inline static size_t sm_numTiles = 0;
			inline static bool sm_tilePressEngaged = false;
		};
	}
}