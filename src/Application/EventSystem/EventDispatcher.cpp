#include "EventDispatcher.hpp"
#include "../GameComponents/Board.hpp"
#include "../GameComponents/Tile.hpp"

namespace App
{
	namespace EventSystem
	{
		/*class InputListener
		{
			InputListener() = default;

			void start();
			void stop();

		private:
			void wt_listenForInputs();
		private:
			std::vector<InputObserver> m_observers;
			std::thread m_listenerThread;
		};*/

		template<class T> requires std::is_base_of_v<BasicEventObserver, T>
		void EventDispatcher::attach(T& observer)
		{
			m_observers.push_back(&observer);
		}

		template<class T> requires std::is_base_of_v<BasicEventObserver, T>
		void EventDispatcher::dettach(T& observer)
		{
			auto it = std::find(m_observers.begin(), m_observers.end(), &observer);
			if (it != m_observers.end())
				m_observers.erase(it);
			else
				std::cout << "WARNING: No observer found InputListener::dettach()\n";
		}

		void EventDispatcher::queueEvent(EventType e)
		{
			m_eventQueue.push_back(e);
		}

		void EventDispatcher::poll()
		{
			SDL_PumpEvents();
			const bool* keyboardState = SDL_GetKeyboardState(nullptr);

			if(!m_eventQueue.empty())
			{
				for (BasicEventObserver* observer : m_observers)
					observer->onInput(keyboardState, m_eventQueue.front());

				m_eventQueue.erase(m_eventQueue.begin());
			}
			else
			{
				for (auto* observer : m_observers)
					observer->onInput(keyboardState, EventType::noEvent);
			}
		}
	}

	template void EventSystem::EventDispatcher::attach<App::GameComponents::Board>(App::GameComponents::Board&);
	template void EventSystem::EventDispatcher::dettach<App::GameComponents::Board>(App::GameComponents::Board&);

	template void EventSystem::EventDispatcher::attach<App::GameComponents::Tile>(App::GameComponents::Tile&);
	template void EventSystem::EventDispatcher::dettach<App::GameComponents::Tile>(App::GameComponents::Tile&);
}