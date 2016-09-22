#include "tilelayer.h"


		TileLayer::TileLayer(radi::graphics::Shader* shader)
			:Layer(new radi::graphics::BatchRenderer2D(), shader, radi::maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
		{			
		}

		TileLayer::~TileLayer()
		{
		}