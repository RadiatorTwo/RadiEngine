#pragma once

#include <vector>
#include <radi_types.h>

#include "buffer.h"
#include "graphics/radi_render_api.h"


namespace radi
{
	namespace graphics
	{
		class VertexArray
		{
		private:
			static uint s_currentBinding;
		private:
			uint m_id;
			std::vector<API::Buffer*> m_buffers;
		public:
			VertexArray();
			~VertexArray();

			API::Buffer* GetBuffer(uint index = 0);
			
			void PushBuffer(API::Buffer* buffer);

			void bind() const;
			void unbind() const;
		};
	}
}
