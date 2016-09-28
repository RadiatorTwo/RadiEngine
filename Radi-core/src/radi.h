#pragma once
#include "radi/graphics/label.h"
#include "radi/graphics/sprite.h"
#include "radi/graphics/renderer2d.h"
#include "radi/graphics/batchrenderer2d.h"
#include "radi/graphics/layers/layer.h"
#include "radi/graphics/layers/group.h"
#include "radi/graphics/texture_manager.h"
#include "radi/graphics/window.h"

#include "radi/graphics/shaders/Shader.h"
#include "radi/graphics/shaders/shader_factory.h"

#include "radi/audio/sound.h"
#include "radi/audio/sound_manager.h"

#include "radi/maths/maths.h"
#include "radi/utils/Log.h"
#include "radi/utils/timer.h"

namespace radi
{
	class Radi
	{
	private:
		graphics::Window* m_window;
		utils::Timer* m_timer;
		int m_framesPerSecond, m_updatesPerSecond;
	protected:
		Radi() :m_framesPerSecond(0), m_updatesPerSecond(0)
		{
		}


		virtual ~Radi()
		{
			delete m_window;
			delete m_timer;
		}

		graphics::Window* createWindow(const char *name, int width, int height)
		{
			m_window = new graphics::Window(name, width, height);
			return m_window;
		}
	public:
		void start()
		{
			init();
			run();
		}

	protected:
		// Runs once upon initialization
		virtual void init() = 0;
		// Runs once per second
		virtual void tick() {}
		// runs 60 times per second;
		virtual void update() {}
		// Runs as fast as possible (unless vsync is enabled)
		virtual void render() = 0;

		const unsigned int getFPS() { return m_framesPerSecond; }
		const unsigned int getUPS() { return m_updatesPerSecond; }

	private:
		void run()
		{
			m_timer = new utils::Timer();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

			while (!m_window->closed())
			{
				m_window->clear();
				if (m_timer->elapsed() - updateTimer > updateTick)
				{
					m_window->updateInput();
					update();
					updates++;
					updateTimer += updateTick;
				}

					render();
					frames++;
					m_window->update();

				if (m_timer->elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_framesPerSecond = frames;
					m_updatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}
			}
		}
	};
}
