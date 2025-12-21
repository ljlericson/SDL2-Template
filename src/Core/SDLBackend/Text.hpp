#pragma once
#include <unordered_map>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>

#include "../AssetManager/AssetManager.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"

#include "../../Utils/Utils.hpp"

namespace Core
{
	namespace SDLBackend
	{
		class Text
		{
		public:
			Text() = default;
			Text(glm::vec2 pos, float w, float h, const std::string& fontFPath, SDL_Color color, const std::string& text);

			void changeColor(SDL_Color color);

			void setText(const std::string& newText);

			void render(const Renderer& renderer);

			SDL_FRect& getRectToSetPosManually();

			SDL_Color getTextColor() const;

			const std::string& getText() const;

		public:
			glm::vec2 pos;
		private:
			struct Font
			{
				Font(const std::string& fpath)
				{
					hnd = TTF_OpenFont(fpath.c_str(), 256);
				}
				~Font()
				{
					TTF_CloseFont(hnd);
				}
				TTF_Font* hnd;
			};
		private:
			std::string m_text;
			std::shared_ptr<Texture> m_tex = nullptr;
			SDL_FRect m_texRect;
			SDL_Color m_col;
			TTF_Font* m_font = nullptr;
			bool m_reloadNeeded = true;
			bool m_manualRectMode = false;

			inline static std::unordered_map<std::string, Font> sm_fonts;
		};
	}
}