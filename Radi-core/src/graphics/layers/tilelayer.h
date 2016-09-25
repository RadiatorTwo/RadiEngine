#pragma once


#include "layer.h"
#include "../batchrenderer2d.h"

class TileLayer : public radi::graphics::Layer
{
public:
	TileLayer(radi::graphics::Shader* shader);
	~TileLayer();
};
