#pragma once

#include <vector>
#include <radi_types.h>

#include "Buffer.h"
#include <graphics/radi_render_api.h>

namespace radi {
	namespace graphics {

		class VertexArray
		{
		private:
			static uint s_CurrentBinding;
		private:
			uint m_ID;
			std::vector<API::Buffer*> m_Buffers;
		public:
			VertexArray();
			~VertexArray();

			API::Buffer* GetBuffer(uint index = 0);

			void PushBuffer(API::Buffer* buffer);
			void Bind() const;
			void Unbind() const;

			// TODO: I don't like this
			void Draw(uint count) const;
		};

	}
}