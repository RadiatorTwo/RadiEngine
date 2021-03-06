#include "radi/rd.h"
#include "fps_camera.h"

#include "radi/app/Input.h"
#include "radi/utils/Log.h"

#include "radi/app/Application.h"
#include "radi/rddebug/debug_menu.h"

namespace radi {
	namespace graphics {

		using namespace maths;

		FPSCamera::FPSCamera(const maths::mat4& projectionMatrix)
			: Camera(projectionMatrix), m_MouseSensitivity(0.002f), m_Speed(4.0f), m_SprintSpeed(m_Speed * 16.0f), m_MouseWasGrabbed(false)
		{
			m_Position = vec3(0.0f, 25.0f, -25.0f);
			m_Rotation = vec3(90.0f, 0.0f, 0.0f);
			m_Yaw = 2.4f;
			m_Pitch = 0.7f;

			debug::DebugMenu::Add("FPS Camera Speed", &m_Speed);
			debug::DebugMenu::Add("FPS Camera Sprint Speed", &m_SprintSpeed);
		}
		
		FPSCamera::~FPSCamera()
		{
			debug::DebugMenu::Remove("FPS Camera Speed");
			debug::DebugMenu::Remove("FPS Camera Sprint Speed");
		}

		void FPSCamera::Focus()
		{
			Input::GetInputManager()->SetMouseCursor(RD_NO_CURSOR);
		}

		void FPSCamera::Update()
		{
			if (Input::IsMouseButtonPressed(RD_MOUSE_RIGHT))
			{
				if (!Input::GetInputManager()->IsMouseGrabbed())
				{
					Input::GetInputManager()->SetMouseGrabbed(true);
					Input::GetInputManager()->SetMouseCursor(RD_NO_CURSOR);
				}
			}

			if (Input::GetInputManager()->IsMouseGrabbed())
			{
				vec2 mouse = Input::GetInputManager()->GetMouseDelta();
				
				if (m_MouseWasGrabbed)
				{
					m_Yaw += mouse.x * m_MouseSensitivity;
					m_Pitch += mouse.y * m_MouseSensitivity;
					if (m_Pitch < -1.5f) m_Pitch = -1.5f;
					if (m_Pitch > 1.75f) m_Pitch = 1.75f;
				}
				m_MouseWasGrabbed = true;

				Quaternion orientation = GetOrientation();
				m_Rotation = orientation.ToEulerAngles() * (180.0f / RD_PI);

				vec3 forward = GetForwardDirection(orientation);
				vec3 right = GetRightDirection(orientation);
				vec3 up = vec3::YAxis();
				float speed = Input::IsKeyPressed(RD_KEY_SHIFT) ? m_SprintSpeed : m_Speed;
				if (Input::IsKeyPressed(RD_KEY_W))
					m_Position += forward * speed;
				else if (Input::IsKeyPressed(RD_KEY_S))
					m_Position -= forward * speed;

				if (Input::IsKeyPressed(RD_KEY_A))
					m_Position -= right * speed;
				else if (Input::IsKeyPressed(RD_KEY_D))
					m_Position += right * speed;

				if (Input::IsKeyPressed(RD_KEY_SPACE))
					m_Position += up * speed;
				if (Input::IsKeyPressed(RD_KEY_CONTROL))
					m_Position -= up * speed;

				mat4 rotation = mat4::Rotate(orientation.Conjugate());
				mat4 translation = mat4::Translate(-m_Position);
				m_ViewMatrix = rotation * translation;
			}

			if (Input::IsKeyPressed(RD_KEY_ESCAPE))
			{
				Input::GetInputManager()->SetMouseGrabbed(false);
				Input::GetInputManager()->SetMouseCursor(1);
				m_MouseWasGrabbed = false;
			}
		}

		Quaternion FPSCamera::GetOrientation() const
		{
			return Quaternion::RotationY(-m_Yaw) * Quaternion::RotationX(-m_Pitch);
		}

		vec3 FPSCamera::GetForwardDirection(const Quaternion& orientation) const
		{
			return Quaternion::Rotate(orientation, -vec3::ZAxis());
		}

		vec3 FPSCamera::GetUpDirection(const Quaternion& orientation) const
		{
			return Quaternion::Rotate(orientation, vec3::YAxis());
		}

		vec3 FPSCamera::GetRightDirection(const Quaternion& orientation) const
		{
			return Quaternion::Rotate(orientation, vec3::XAxis());
		}

	}
}