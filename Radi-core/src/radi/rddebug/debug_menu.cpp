#include "radi/rd.h"
#include "debug_menu.h"

#include "debug_menu_action.h"

#include "radi/app/Window.h"
#include "radi/graphics/ui/Button.h"

#include "radi/system/Memory.h"

namespace radi {
	namespace debug {

		using namespace maths;
		using namespace graphics;
		using namespace ui;

		DebugMenu* DebugMenu::s_Instance = nullptr;

		DebugMenu::DebugMenu()
			: m_Visible(false), m_Slider(nullptr), m_Path(nullptr)
		{
			s_Instance = this;

			// Default settings
			m_Settings.horizontalPadding = 0.4f;
			m_Settings.verticalPadding = 0.6f;
			m_Settings.fontSize = 20.0f;

			Add("Debug Menu/Horizontal Padding", &m_Settings.horizontalPadding, 0.0f, 4.0f);
			Add("Debug Menu/Vertical Padding", &m_Settings.verticalPadding, 0.0f, 4.0f);
			Add("Debug Menu/Font Size", &m_Settings.fontSize, 8.0f, 48.0f);

			m_Slider = rdnew Slider*[4];
			m_Panel = rdnew Panel();
		}

		DebugMenu* DebugMenu::Get()
		{
			return s_Instance;
		}

		void DebugMenu::Init()
		{
			RADI_ASSERT(s_Instance == nullptr); // There should only ever be ONE Debug Menu!
			rdnew DebugMenu();
		}

		void DebugMenu::Add(const String& path)
		{
			s_Instance->Add(path, rdnew EmptyAction(path));
		}

		void DebugMenu::Add(const String& path, bool* value)
		{
			s_Instance->Add(path, rdnew BooleanAction(path, [value]() { return *value; }, [value](bool v) { *value = v; }));
		}

		void DebugMenu::Add(const String& path, float* value)
		{
			Add(path, value, 0.0f, 100.0f);
		}

		void DebugMenu::Add(const String& path, float* value, float minimum, float maximum)
		{
			s_Instance->Add(path, rdnew FloatAction(path, [value]() { return *value; }, [value](float v) { *value = v; }, minimum, maximum));
		}

		void DebugMenu::Add(const String& path, vec2* value, float minimum, float maximum)
		{
			s_Instance->Add(path, rdnew Vec2Action(path, [value]() { return *value; }, [value](vec2 v) { *value = v; }, vec2(minimum), vec2(maximum)));
		}

		void DebugMenu::Add(const String& path, vec3* value, float minimum, float maximum)
		{
			s_Instance->Add(path, rdnew Vec3Action(path, [value]() { return *value; }, [value](vec3 v) { *value = v; }, vec3(minimum), vec3(maximum)));
		}

		void DebugMenu::Add(const String& path, vec4* value, float minimum, float maximum)
		{
			s_Instance->Add(path, rdnew Vec4Action(path, [value]() { return *value; }, [value](vec4 v) { *value = v; }, vec4(minimum), vec4(maximum)));
		}

		void DebugMenu::Add(const String& path, IAction* action)
		{
			if (StringContains(path, "/"))
			{
				std::vector<String> paths = SplitString(path, "/");
				action->name = paths.back();
				paths.pop_back();
				PathAction* pathAction = CreateOrFindPaths(paths);
				RADI_ASSERT(pathAction);
				if (!pathAction->ContainsAction(action->name))
					pathAction->actionList.push_back(action);
				else
					rddel action;
			}
			else
			{
				m_ActionList.push_back(action);
			}
			Refresh();
		}

		PathAction* DebugMenu::CreateOrFindPaths(std::vector<String>& paths, PathAction* action)
		{
			if (paths.empty())
				return action;

			String name = paths.front();
			paths.erase(paths.begin());

			ActionList* actionList = action ? &action->actionList : &m_ActionList;
			for (IAction* a : *actionList)
			{
				if (a->type == IAction::Type::PATH && a->name == name)
					return CreateOrFindPaths(paths, (PathAction*)a);
			}

			PathAction* pathAction = rdnew PathAction(name, action);
			actionList->push_back(pathAction);
			return CreateOrFindPaths(paths, pathAction);
		}

		void DebugMenu::Remove(const String& path)
		{
			if (StringContains(path, "/"))
			{
				std::vector<String> paths = SplitString(path, "/");
				String name = paths.back();
				paths.pop_back();
				PathAction* pathAction = s_Instance->CreateOrFindPaths(paths);
				RADI_ASSERT(pathAction);
				if (pathAction->ContainsAction(name))
				{
					if (pathAction->actionList.size() == 1)
					{
						PathAction* parent = pathAction->parent;
						if (parent)
						{
							parent->DeleteChild(pathAction);
						}
						else
						{
							for (uint i = 0; i < s_Instance->m_ActionList.size(); i++)
							{
								if (s_Instance->m_ActionList[i] == pathAction)
								{
									rddel s_Instance->m_ActionList[i];
									s_Instance->m_ActionList.erase(s_Instance->m_ActionList.begin() + i);
									break;
								}
							}
						}
						while (parent)
						{
							rddel pathAction;
							pathAction = pathAction->parent;
						}
					}
					else
					{
						ActionList& actionList = pathAction->actionList;
						for (uint i = 0; i < actionList.size(); i++)
						{
							if (actionList[i]->name == name)
							{
								actionList.erase(actionList.begin() + i);
								break;
							}
						}
					}
				}
			}
			else
			{
				ActionList& actions = s_Instance->m_ActionList;
				for (uint i = 0; i < actions.size(); i++)
				{
					if (actions[i]->name == path)
					{
						rddel actions[i];
						actions.erase(actions.begin() + i);
						break;
					}
				}
			}
			s_Instance->Refresh();
		}

		PathAction* DebugMenu::FindPath(const String& name)
		{
			for (IAction* action : m_ActionList)
			{
				if (action->type == IAction::Type::PATH)
				{
					PathAction* a = (PathAction*)action;
					if (a->name == name)
						return a;
					else
						a->FindPath(name);
				}
			}
			return nullptr;
		}

		bool DebugMenu::IsVisible()
		{
			return s_Instance->m_Visible;
		}

		void DebugMenu::SetVisible(bool visible)
		{
			s_Instance->m_Visible = visible;
			if (visible)
				s_Instance->OnActivate();
			else
				s_Instance->OnDeactivate();
		}

		void DebugMenu::SetPath(PathAction* path)
		{
			s_Instance->m_Path = path;
			s_Instance->Refresh();
		}

		DebugMenuSettings& DebugMenu::GetSettings()
		{
			return s_Instance->m_Settings;
		}

		bool DebugMenu::OnMousePressed(events::MousePressedEvent& e)
		{
			return false;
		}

		bool DebugMenu::OnMouseReleased(events::MouseReleasedEvent& e)
		{
			return false;
		}

		void DebugMenu::OnActivate()
		{
			float maxWidth = 0.0f;
			float height = m_Settings.verticalPadding;
			float yOffset = height;

			ActionList* actionList = m_Path ? &m_Path->actionList : &m_ActionList;
			if (m_Path)
			{
				DebugMenuItem* item = rdnew DebugMenuItem(rdnew BackAction(m_Path->parent), Rectangle(0.0f, 18.0f - yOffset, 0.0f, height));
				m_Panel->Add(item);
				yOffset += height * 2.0f;
				maxWidth = item->GetFont().GetWidth(item->GetAction()->ToString()) * 0.5f;
			}

			for (IAction* action : *actionList)
			{
				float y = 18.0f - yOffset;
				DebugMenuItem* item = rdnew DebugMenuItem(action, Rectangle(0.0f, y, 0.0f, height));
				m_Panel->Add(item);
				yOffset += height * 2.0f;

				const Font& font = item->GetFont();
				float stringWidth = font.GetWidth(item->GetAction()->ToString()) * 0.5f;
				if (stringWidth > maxWidth)
					maxWidth = stringWidth;
			}

			maxWidth += m_Settings.horizontalPadding;
			for (Widget* widget : m_Panel->GetWidgets())
			{
				DebugMenuItem* item = (DebugMenuItem*)widget;
				Rectangle& bounds = item->GetBounds();
				bounds.x = maxWidth;
				bounds.width = maxWidth;
			}

			const float sliderWidth = 0.75f;
			float sliderX = maxWidth * 2.0f + sliderWidth;
			for (uint i = 0; i < 4; i++)
			{
				m_Slider[i] = rdnew Slider({ sliderX + i * sliderWidth * 2.0f, 9.0f, sliderWidth, 9.0f }, true);
				m_Panel->Add(m_Slider[i])->SetActive(false);
			}
		}

		void DebugMenu::OnDeactivate()
		{
			m_Panel->Clear();
		}

		void DebugMenu::Refresh()
		{
			if (!m_Panel || !IsVisible())
				return;

			OnDeactivate();
			OnActivate();
		}

		void DebugMenu::EditValues(const String& name, float* values, uint count, const Slider::ValueChangedCallback* callbacks)
		{
			for (uint i = 0; i < 4; i++)
			{
				m_Slider[i]->SetActive(false);
				if (i < count)
				{
					m_Slider[i]->SetCallback(callbacks[i]);
					m_Slider[i]->SetActive(m_LastEditedName != name);
					m_Slider[i]->SetValue(values[i]);
				}
			}
			m_LastEditedName = m_LastEditedName != name ? name : "";
		}

		void DebugMenu::OnUpdate()
		{
		}

		void DebugMenu::OnRender(graphics::Renderer2D& renderer)
		{
		}

	}
}