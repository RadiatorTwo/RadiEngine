#pragma once

#include "radi/rd.h"
#include "radi/graphics/renderer2d.h"
#include "radi/graphics/layers/layer2D.h"

namespace radi {
	namespace graphics {
		namespace ui {

			class Widget;

			class Panel : public Layer2D
			{
			private:
				std::vector<Widget*> m_Widgets;
			public:
				Panel();
				~Panel();

				Widget* Add(Widget* widget);
				void Remove(Widget* widget);
				void Clear();

				void OnEvent(events::Event& e) override;
				bool OnMousePressedEvent(events::MousePressedEvent& e);
				bool OnMouseReleasedEvent(events::MouseReleasedEvent& e);
				bool OnMouseMovedEvent(events::MouseMovedEvent& e);

				void OnUpdate() override;
				void OnRender(Renderer2D& renderer) override;
			};

		}
	}
}