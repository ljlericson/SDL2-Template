#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include <SDL3/SDL.h>

namespace Core
{
	namespace SDLBackend { struct Texture; }

	namespace AssetManager
	{
		class TextureManager
		{
		public:
			TextureManager() = default;

			std::shared_ptr<SDLBackend::Texture> newTexture(const std::string& key, SDL_Renderer* renderer, const std::string& fpath);

			std::shared_ptr<SDLBackend::Texture> newTexture(const std::string& key, SDL_Renderer* renderer, SDL_Texture* texture);

			std::shared_ptr<SDLBackend::Texture> overwriteTexture(const std::string& key, SDL_Renderer* renderer, const std::string& fpath);

			std::shared_ptr<SDLBackend::Texture> overwriteTexture(const std::string& key, SDL_Renderer* renderer, SDL_Texture* texture);

			std::shared_ptr<SDLBackend::Texture> getTexture(const std::string& key);

			std::shared_ptr<SDLBackend::Texture> getInvalidTex();

			void runGarbargeCollector();

			bool contains(const std::string& key) const;

		private:
			std::unordered_map<std::string, std::shared_ptr<SDLBackend::Texture>> m_textures;
			std::shared_ptr<SDLBackend::Texture> m_invalidTex;

			SDL_Renderer* mrp_renderer = nullptr; // REFERENCE POINTER NOT OWNED
		};
	}
}