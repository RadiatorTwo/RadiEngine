#pragma once

#include <radi_types.h>
#include "../../events/Event.h"
#include "../../events/IEventListener.h"
#include "../Window.h"
#include "../../maths/maths.h"

namespace radi
{
	namespace graphics
	{
		using namespace graphics;
		using namespace maths;

		class Layer : public events::IEventListener
		{
		protected:
			Window* m_window;

		public:
			Layer();
			virtual ~Layer();

			virtual void Init();
			virtual bool OnEvent(const events::Event& event);
			virtual void OnTick();
			virtual void OnUpdate();
			virtual void OnRender();
		};

	}
}