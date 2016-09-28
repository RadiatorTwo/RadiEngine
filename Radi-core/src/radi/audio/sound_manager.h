#pragma once

#include "radi/rd.h"
#include "radi/common.h"
#include "sound.h"

struct gau_Manager;
struct ga_Mixer;

namespace radi { namespace audio {

	class RD_API SoundManager
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