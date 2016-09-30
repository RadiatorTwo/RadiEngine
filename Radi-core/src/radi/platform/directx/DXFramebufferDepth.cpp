#include "radi/rd.h"
#include "DXFramebufferDepth.h"

namespace radi { namespace graphics {

	D3DFramebufferDepth::D3DFramebufferDepth(uint width, uint height)
		: m_Width(width), m_Height(height)
	{
		Init();
	}

	D3DFramebufferDepth::~D3DFramebufferDepth()
	{
	}

	void D3DFramebufferDepth::Init()
	{

	}

	void D3DFramebufferDepth::Bind() const
	{
	}

	void D3DFramebufferDepth::Unbind() const
	{
	}

	void D3DFramebufferDepth::Clear()
	{
	}

} }