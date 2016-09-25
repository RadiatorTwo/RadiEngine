#include <radigl.h>
#include <radi_types.h>

#include <graphics/Window.h>
#include <utils/Timer.h>

namespace radi {

	class Application
	{
	public:
		graphics::Window* window;
	private:
		bool m_running, m_suspended;
		utils::Timer* m_Timer;
		uint m_updatesPerSecond, m_framesPerSecond;

		const char* m_name;
		uint m_width, m_height;
	public:
		Application(const char* name, uint width, uint height);
		virtual ~Application();

		virtual void Init();

		void Start();
		void Suspend();
		void Resume();
		void Stop();

		virtual void Tick();
		virtual void Update();
		virtual void Render();

		const uint GetFPS() const { return m_framesPerSecond; }
		const uint GetUPS() const { return m_updatesPerSecond; }
	private:
		void Run();
	};


}