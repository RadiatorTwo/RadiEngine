#pragma once

#include "radi/rd.h"
#include "radi/Common.h"
#include "Sound.h"

struct gau_Manager;
struct ga_Mixer;

namespace radi {
	namespace audio {

		class RD_API SoundManager
		{
		private:
			friend class Sound;

			static gau_Manager* m_Manager;
			static ga_Mixer* m_Mixer;

			static std::vector<Sound*> m_Sounds;
		public:
			static void Init();
			static Sound* Add(Sound* sound);
			static Sound* Get(const String& name);
			static void Update();
			static void Clean();
		private:
			SoundManager() { }
		};

	}
}