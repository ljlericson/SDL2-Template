#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include <SDL3/SDL.h>


namespace Core
{
	namespace SDLBackend
	{
		class Window
		{
		public:
			Window(const std::string& title, uint16_t w, uint16_t h);
			
			void pollEvents();
			void changeWinName(const std::string& name);
			bool shouldClose();

			const std::vector<uint32_t>& getUnhandledEvents() const;
			SDL_Window* getWHand() const;

		private:
			std::vector<uint32_t> m_eventsToHandle;

			uint16_t m_w, m_h;
			SDL_Window* m_whand;
			SDL_Event m_event;
		};
	}
}