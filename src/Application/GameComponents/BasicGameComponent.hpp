#include "../EventSystem/BasicEventObserver.hpp"
#include "../../Core/SDL2Backend/Renderer.hpp"

namespace App
{
	namespace GameComponents
	{
		class BasicGameComponent : public EventSystem::BasicEventObserver
		{
		public:
			virtual ~BasicGameComponent() = default;

			virtual void render(const Core::SDLBackend::Renderer& renderer) const = 0;

			virtual void onInput(const bool* keyboardState, EventType e) override = 0;
		};
	}
}