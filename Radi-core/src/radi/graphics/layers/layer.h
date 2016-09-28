#pragma once

#include "radi/common.h"
#include "radi/radi_types.h"

#include "../../events/Event.h"
#include "../../events/IEventListener.h"
#include "../Window.h"

namespace radi
{
	namespace graphics
	{
		using namespace graphics;
		using namespace maths;

		class RD_API Layer : public events::IEventListener
		{
		protected:
			Window* m_window;

		public:
			Layer();
			virtual ~Layer();

			virtual void Init();
			virtual void OnEvent(events::Event& event);
			virtual void OnTick();
			virtual void OnUpdate();
			virtual void OnRender();
		};

	}
}