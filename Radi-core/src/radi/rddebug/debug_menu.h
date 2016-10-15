#pragma once

#include "radi/rd.h"
#include "radi/graphics/Renderer2D.h"
#include "radi/graphics/ui/Panel.h"

#include "debug_menu_item.h"
#include "debug_menu_slider.h"
#include "radi/graphics/ui/Slider.h"

namespace radi {
	namespace debug {

		struct IAction;
		struct PathAction;
		typedef std::vector<IAction*> ActionList;

		struct DebugMenuSettings
		{
			float horizontalPadding, verticalPadding;
			float fontSize;
		};

		class RD_API DebugMenu
		{
		private:
			static DebugMenu* s_Instance;
		private:
			bool m_Visible;
			DebugMenuSettings m_Settings;
			ActionList m_ActionList;
			PathAction* m_Path;

			graphics::ui::Panel* m_Panel;
			graphics::ui::Slider** m_Slider;
			String m_LastEditedName;
		public:
			static DebugMenu* Get();

			static void Init();
			static void Add(const String& path);
			static void Add(const String& path, bool* value);
			static void Add(const String& path, float* value);
			static void Add(const String& path, float* value, float mininmum, float maximum);
			static void Add(const String& path, maths::vec2* value, float mininmum = 0.0f, float maximum = 100.0f);
			static void Add(const String& path, maths::vec3* value, float mininmum = 0.0f, float maximum = 100.0f);
			static void Add(const String& path, maths::vec4* value, float mininmum = 0.0f, float maximum = 100.0f);

			static void Remove(const String& path);

			PathAction* FindPath(const String& path);

			static bool IsVisible();
			static void SetVisible(bool visible);

			static void SetPath(PathAction* path);

			static DebugMenuSettings& GetSettings();

			void OnActivate();
			void OnDeactivate();
			void EditValues(const String& name, float* values, uint count, const graphics::ui::Slider::ValueChangedCallback* callback);

			bool OnMousePressed(events::MousePressedEvent& e);
			bool OnMouseReleased(events::MouseReleasedEvent& e);
			void OnUpdate();
			void OnRender(graphics::Renderer2D& renderer);
		private:
			DebugMenu();

			void Refresh();

			void Add(const String& path, IAction* action);
			PathAction* CreateOrFindPaths(std::vector<String>& paths, PathAction* action = nullptr);
		};

	}
}