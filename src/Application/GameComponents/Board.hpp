#pragma once
#include <expected>
#include <memory>

#include <SDL3/SDL.h>

#include "BasicGameComponent.hpp"
#include "../../Core/SDL2Backend/Renderer.hpp"
#include "../../Core/SDL2Backend/Window.hpp"
#include "../../Core/AssetManager/AssetManager.hpp"
#include "../../Core/SDL2Backend/Texture.hpp"
#include "../../Utils/Utils.hpp"

namespace App
{
	namespace GameComponents
	{
		class Board : public BasicGameComponent
		{
		public:
			enum class SnapErrType
			{
				tooFarFromBoard,
				spotOccupied
			};

			Board() = default;

			Board(const Core::SDLBackend::Renderer& renderer, const Core::SDLBackend::Window& window);

			void render(const Core::SDLBackend::Renderer& renderer) const override;

			void onInput(const bool* keyboardState, EventType e) override;

			auto snapTile(glm::vec2 pos) -> std::expected<std::pair<glm::vec2, size_t>, SnapErrType>;

			size_t getSnapTileIndex(glm::vec2 pos);

			void unCheckTile(size_t tile);

			size_t getNumTiles() const;

		private:
			Core::SDLBackend::Texture* m_tex = nullptr;
			mutable SDL_FRect m_texRect;
			mutable SDL_FRect m_texRectShaking;

			// config items
			size_t m_numTiles = 15; // number of tiles lengthwise |--->|
			std::unique_ptr<bool[]> m_occupiedTiles;
		};
	}
}

