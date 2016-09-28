#pragma once

#include "radi/rd.h"
#include "radi/common.h"

#include "component/components.h"

namespace radi {
	namespace entity {

		class RD_API Entity
		{
		protected:
			std::vector<component::Component*> m_Components;
		public:
			Entity();

			void AddComponent(component::Component* component);

			template <typename T>
			const T* GetComponent() const
			{
				return GetComponentInternal<T>();
			}

			template <typename T>
			T* GetComponent()
			{
				return (T*)GetComponentInternal<T>();
			}
		private:
			template <typename T>
			const T* GetComponentInternal() const
			{
				component::ComponentType* type = T::GetStaticType();
				for (auto x : m_Components)
				{
					if (x->GetType() == type)
						return (const T*)x;
				}
				return nullptr;
			}
		};

	}
}