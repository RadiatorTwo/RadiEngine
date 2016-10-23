#pragma once

#include <radi.h>

class Test2D : public radi::graphics::Layer2D
{
private:
	radi::graphics::Label** debugInfo;
	radi::graphics::Renderer2D* m_Renderer;

	radi::graphics::Sprite* m_marioSprite;
	radi::entity::Entity* m_mario;

	radi::graphics::API::Texture2D* m_texMarioBigStill;
	radi::graphics::API::Texture2D* m_texMarioBigWalk;
	radi::graphics::API::Texture2D* m_texMarioBigRun;

	std::vector<radi::graphics::Sprite*> m_backgroundArray;
	radi::graphics::API::Texture2D* m_texBackground1;
	radi::graphics::API::Texture2D* m_texBackground2;
	radi::graphics::API::Texture2D* m_texBackground3;

	std::vector<radi::graphics::Sprite*> m_groundTileArray;
	radi::graphics::API::Texture2D* m_texGroundTileLeft;
	radi::graphics::API::Texture2D* m_texGroundTileMiddle;
	radi::graphics::API::Texture2D* m_texGroundTileRight;

public:
	Test2D();
	~Test2D();

	void OnInit(radi::graphics::Renderer2D& renderer, radi::graphics::Material& material) override;

	void OnTick() override;
	void OnUpdate(const radi::Timestep& ts) override;

	bool OnKeyPressedEvent(radi::events::KeyPressedEvent& event);
	bool OnMousePressedEvent(radi::events::MousePressedEvent& event);
	void OnEvent(radi::events::Event& event) override;

	void OnRender(radi::graphics::Renderer2D& renderer) override;
};