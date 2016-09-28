#pragma once

#include "radi/rd.h"
#include "radi/common.h"
#include "radi/radi_types.h"
#include "radi/radi_string.h"

struct ga_Sound;
struct ga_Handle;

namespace radi { namespace audio {

	class Sound
	{
	private:
		String m_Name;
		String m_Filename;

		uint m_Count;

		ga_Sound* m_Sound;
		ga_Handle* m_Handle;
		int m_Position;

		bool m_Playing;
		float m_Gain;
	public:
		Sound(const String& name, const String& filename);
		~Sound();


		void play();
		void loop();
		void pause();
		void resume();
		void stop();

		void setGain(float gain);

		inline const bool isPlaying() const { return m_Playing; }
		inline const float getGain() const { return m_Gain; }
		inline const String& getName() const { return m_Name; }
		inline const String& getFileName() const { return m_Filename; }

		friend void destroy_on_finish(ga_Handle* in_handle, void* in_context);
		friend void loop_on_finish(ga_Handle* in_handle, void* in_context);

	};

} }