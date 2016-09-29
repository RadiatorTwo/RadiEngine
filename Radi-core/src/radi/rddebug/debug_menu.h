#pragma once

#include "radi/rd.h"
#include "radi/graphics/Renderer2D.h"

namespace radi {
	namespace debug {

		struct DebugMenuItem
		{
			String name;
		};

		class DebugMenu
		{
		private:
			static DebugMenu* s_Instance;
		private:
			bool m_Visible;
			std::vector<DebugMenuItem> m_DebugMenuItems;
		public:
			static void Init();
			static void Add(const String& name);

			static bool IsVisible();
			static void SetVisible(bool visible);

			static void OnRender(graphics::Renderer2D& renderer);
		private:
			DebugMenu();
		};

	}
}