#pragma once

#include <vector>

#include "sound.h"

#define GAU_THREAD_POLICY_MULTI 2
#include "../../gorilla-audio/src/ga.h"
#include "../../gorilla-audio/src/gau.h"

namespace radi { namespace audio {

	class SoundManager
	{
	private:
		friend class Sound;

		static gau_Manager* m_Manager;
		static ga_Mixer* m_Mixer;

		static std::vector<Sound*> m_Sounds;
	public:
		static void init();
		static Sound* add(Sound* sound);
		static Sound* get(const String& name);
		static void update();
		static void clean();
	private:
		SoundManager() { }
	};

} }