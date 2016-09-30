#include "radi/rd.h"
#include "debug_menu_item.h"
#include "debug_menu_action.h"

#include "radi/graphics/font_manager.h"

#include "debug_menu.h"

namespace radi {
	namespace debug {

		using namespace graphics;

		DebugMenuItem::DebugMenuItem(IAction* action, const maths::Rectangle& bounds)
			: Button(action->ToString(), bounds, [action]() { action->OnAction(); }), m_Action(action)
		{
		}

		void DebugMenuItem::OnUpdate()
		{
			m_Label = m_Action->ToString();
			m_Font = FontManager::Get((uint)DebugMenu::Get()->GetSettings().fontSize);
		}

	}
}