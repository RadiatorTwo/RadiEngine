#pragma once

#include "radi/common.h"
#include "radi/radi_types.h"
#include "radi/radi_string.h"

namespace radi {
	namespace entity {
		class Entity;
	}
}

namespace radi {
	namespace entity {
		namespace component {

			struct RD_API ComponentType
			{
				String name;
			};

			class RD_API Component
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