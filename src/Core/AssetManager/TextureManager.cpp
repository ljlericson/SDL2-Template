#include "TextureManager.hpp"
#include "../SDLBackend/Texture.hpp"

namespace Core
{
	namespace AssetManager
	{
		std::shared_ptr<SDLBackend::Texture> TextureManager::newTexture(const std::string& key, SDL_Renderer* renderer, const std::string& fpath)
		{
			if (!mrp_renderer && renderer)
				mrp_renderer = renderer;

			// avoid texture creation if texture exists
			if(m_textures.contains(key))
				return m_textures.at(key);

			auto tex = std::make_shared<SDLBackend::Texture>(renderer, fpath);

			if (tex->texHand)
			{
				m_textures.insert({ key, std::move(tex) });
				
				return m_textures.at(key);
			}
			// texture is invalid so we return the invalid tex
			else
			{
				return this->getInvalidTex();
			}
		}

		std::shared_ptr<SDLBackend::Texture> TextureManager::newTexture(const std::string& key, SDL_Renderer* renderer, SDL_Texture* texture)
		{
			if (!mrp_renderer && renderer)
				mrp_renderer = renderer;

			// avoid texture creation if texture exists
			if (m_textures.contains(key))
				return m_textures.at(key);

			auto tex = std::make_shared<SDLBackend::Texture>(texture);

			if (tex->texHand)
			{
				m_textures.insert({ key, std::move(tex) });

				return m_textures.at(key);
			}
			// texture is invalid so we return the invalid tex
			else
			{
				return this->getInvalidTex();
			}
		}

		std::shared_ptr<SDLBackend::Texture> TextureManager::overwriteTexture(const std::string& key, SDL_Renderer* renderer, const std::string& fpath)
		{
			if (!mrp_renderer)
				mrp_renderer = renderer;

			// avoid texture creation if texture exists
			if (!m_textures.contains(key))
			{
				std::cout << "ERROR: NO TEXTURE TO OVERWRITE\n";
				return this->getInvalidTex();
			}

			auto tex = std::make_shared<SDLBackend::Texture>(renderer, fpath);

			if (tex->texHand)
			{
				m_textures.at(key) = tex;

				return m_textures.at(key);
			}
			// texture is invalid so we return the invalid tex
			else
			{
				return this->getInvalidTex();
			}
		}

		std::shared_ptr<SDLBackend::Texture> TextureManager::overwriteTexture(const std::string& key, SDL_Renderer* renderer, SDL_Texture* texture)
		{
			if (!mrp_renderer)
				mrp_renderer = renderer;

			// avoid texture creation if texture exists
			if (!m_textures.contains(key))
			{
				std::cout << "ERROR: NO TEXTURE TO OVERWRITE\n";
				return this->getInvalidTex();
			}

			auto tex = std::make_shared<SDLBackend::Texture>(texture);

			if (tex->texHand)
			{
				m_textures.at(key) = tex;

				return m_textures.at(key);
			}
			// texture is invalid so we return the invalid tex
			else
			{
				return this->getInvalidTex();
			}
		}

		std::shared_ptr<SDLBackend::Texture> TextureManager::getTexture(const std::string& key)
		{
			if (m_textures.contains(key))
				return m_textures.at(key);
			
			else
			{
				std::cout << "WARNING: NO TEXTURE FOUND TextureManager::getTexture()\n";
				return this->getInvalidTex();
			}
		}

		std::shared_ptr<SDLBackend::Texture> TextureManager::getInvalidTex()
		{
			if (!m_invalidTex)
				m_invalidTex = std::make_shared<SDLBackend::Texture>(mrp_renderer, "./assets/Textures/LoadingError.png");

			return m_invalidTex;
		}

		void TextureManager::runGarbargeCollector()
		{
			std::vector<std::string> keysToFree;
			for (const auto& [key, ptr] : m_textures)
			{
				// use count of 1 means only TextureManager
				// has a reference, thus it is not in use
				// and is simply wasted memory
				if (ptr.use_count() == 1)
					keysToFree.push_back(key);
			}
			for (const auto& key : keysToFree)
				m_textures.erase(key);
		}

		bool TextureManager::contains(const std::string& key) const
		{
			return m_textures.contains(key);
		}
	}
}