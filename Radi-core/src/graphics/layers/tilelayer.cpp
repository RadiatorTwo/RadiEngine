#include "tilelayer.h"

#include "maths/tvec2.h"

TileLayer::TileLayer(radi::graphics::Shader* shader)
	: Layer(new radi::graphics::BatchRenderer2D(radi::maths::tvec2<uint>(0, 0)), shader, radi::maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{
}

TileLayer::~TileLayer()
{
}