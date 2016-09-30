#pragma once

#include "radi/graphics/API/VertexArray.h"

namespace radi { namespace graphics { namespace API {

	class D3DVertexArray : public VertexArray
	{
	private:
		uint m_Handle;
		std::vector<API::VertexBuffer*> m_Buffers;
	public:
		D3DVertexArray();
		~D3DVertexArray();

		inline API::VertexBuffer* GetBuffer(uint index = 0) override { return m_Buffers[index]; }
		void PushBuffer(API::VertexBuffer* buffer) override;

		void Bind() const override;
		void Unbind() const override;

		void Draw(uint count) const override;
	};

} } }
