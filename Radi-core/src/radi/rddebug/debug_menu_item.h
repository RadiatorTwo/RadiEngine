#pragma once

#include "radi/rd.h"

#include "radi/graphics/ui/Button.h"
#include "radi/maths/maths.h"

namespace radi {
	namespace debug {

		struct IAction;

		class DebugMenuItem : public graphics::ui::Button
		{
		private:
			IAction* m_Action;
		public:
			DebugMenuItem(IAction* action, const maths::Rectangle& bounds);

			void OnUpdate() override;
		};

	}
}