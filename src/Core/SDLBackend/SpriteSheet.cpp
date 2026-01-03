#include "SpriteSheet.hpp"

namespace Core
{
	namespace SDLBackend
	{
		SpriteSheet::SpriteSheet(SDL_Renderer* renderer, const std::string& fpath, int frameW, int frameH, int numFramesX, int numFramesY)
		: m_texHand(AssetManager::textureManager->newTexture("AnimatedTexture:" + fpath, renderer, fpath)),
			  pos(0.0f),
			  m_frameW(frameW),
			  m_frameH(frameH),
			  m_numFramesX(numFramesX),
			  m_numFramesY(numFramesY)
		{
			m_texRect = SDL_FRect{ 0.0f, 0.0f, static_cast<float>(frameW), static_cast<float>(frameH) };
			m_srcRect = SDL_FRect{ 0.0f, 0.0f, static_cast<float>(frameW), static_cast<float>(frameH) };
		}

		SpriteSheet::SpriteSheet(SDL_Texture* texture, int frameW, int frameH, int numFramesX, int numFramesY)
		: m_texHand(AssetManager::textureManager->newTexture("AnimatedTexture:FromSDLTexture", nullptr, texture)),
			  pos(0.0f),
			  m_frameW(frameW),
			  m_frameH(frameH),
			  m_numFramesX(numFramesX),
			  m_numFramesY(numFramesY)
		{
			m_texRect = SDL_FRect{ 0.0f, 0.0f, static_cast<float>(frameW), static_cast<float>(frameH) };
			m_srcRect = SDL_FRect{ 0.0f, 0.0f, static_cast<float>(frameW), static_cast<float>(frameH) };
		}

		void SpriteSheet::render(const Renderer& renderer)
		{
			m_srcRect.x = static_cast<float>((m_currentFrame % m_numFramesX) * m_frameW);
			m_srcRect.y = static_cast<float>((m_currentFrame / m_numFramesX) * m_frameH);
			m_texRect.x = pos.x;
			m_texRect.y = pos.y;
			renderer.render(*m_texHand, m_texRect, &m_srcRect);
		}

		void SpriteSheet::setFrame(int frame)
		{
			if (frame < 0 || frame >= m_numFramesX * m_numFramesY)
			{
				std::cerr << "ERROR: AnimatedTexture::setAnimationFrame() - frame out of bounds\n";
				return;
			}
			m_currentFrame = frame;
		}
	}
}