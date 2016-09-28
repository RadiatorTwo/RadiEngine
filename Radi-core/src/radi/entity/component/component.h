#pragma once

#include <radi_types.h>

namespace radi {
	namespace entity {
		class Entity;
	}
}

namespace radi {
	namespace entity {
		namespace component {

			struct ComponentType
			{
				String name;
			};

			class Component
			{
			protected:
				Entity* m_Entity;
			public:
				virtual Entity* GetEntity() { return m_Entity; }
				virtual ComponentType* GetType() const { return nullptr; }
			};

		}
	}
}