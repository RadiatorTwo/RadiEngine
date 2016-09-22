#pragma once
#include "../src/graphics/layers/layer.h"
#include "../src/graphics/batchrenderer2d.h"

class TileLayer : public radi::graphics::Layer
{
public:
	TileLayer(radi::graphics::Shader* shader);
	~TileLayer();
};
