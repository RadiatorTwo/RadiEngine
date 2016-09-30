#include "radi/rd.h"
#include "DXFramebuffer2D.h"

#include "radi/system/Memory.h"
#include "radi/utils/Log.h"

namespace radi { namespace graphics {

	using namespace API;

	D3DFramebuffer2D::D3DFramebuffer2D(uint width, uint height)
		: m_Width(width), m_Height(height)
	{
		Init();
	}

	D3DFramebuffer2D::~D3DFramebuffer2D()
	{
		
	}

	void D3DFramebuffer2D::Init()
	{

	}

	void D3DFramebuffer2D::Bind() const
	{

	}

	void D3DFramebuffer2D::Unbind() const
	{

	}

	void D3DFramebuffer2D::Clear()
	{

	}

} }