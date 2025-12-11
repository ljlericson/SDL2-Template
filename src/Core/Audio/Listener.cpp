#include "Listener.hpp"

namespace Core
{
	namespace Audio
	{
		Listener::Listener(glm::vec3 pos)
		  : pos(pos), 
			orientation{{
				0.0f, 0.0f, -1.0f, // orientation
				0.0f, 1.0f, 0.0f   // up
			}}
		{
			m_device = alcOpenDevice(nullptr);
			if (!m_device) std::cout << "Failed to open audio device\n";

			m_context = alcCreateContext(m_device, nullptr);
			if (!m_context) std::cout << "Failed to create audio context\n";

			alcMakeContextCurrent(m_context);
			alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
			alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
		}
		
		Listener::~Listener()
		{
			if (m_device && m_context)
			{
				alcDestroyContext(m_context);
				alcCloseDevice(m_device);
			}
		}

		void Listener::update() const
		{
			alListenerfv(AL_ORIENTATION, orientation.data());
			alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
		}
	}
}