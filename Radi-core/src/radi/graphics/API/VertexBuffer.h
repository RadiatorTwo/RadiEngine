#pragma once

#include "radi/radi_types.h"
#include "radi/graphics/API/buffer_layout.h"
#include "radi/system/Memory.h"

namespace radi { namespace graphics { namespace API {

	enum class BufferUsage
	{
		STATIC, DYNAMIC
	};

	class VertexBuffer
	{
	public:
		virtual void Resize(uint size) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void SetData(uint size, const void* data) = 0;

		virtual void ReleasePointer() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		template<typename T>
		T* GetPointer()
		{
			return (T*)GetPointerInternal();
		}
	protected:
		virtual void* GetPointerInternal() = 0;
	public:
		static VertexBuffer* Create(BufferUsage usage = BufferUsage::STATIC);
	};


} } }