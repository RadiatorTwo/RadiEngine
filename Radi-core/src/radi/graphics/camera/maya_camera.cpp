#include "radi/rd.h"
#include "maya_camera.h"

#include "radi/app/Window.h"
#include "radi/app/Input.h"

#include "radi/utils/Log.h"

namespace radi {
	namespace graphics {

		using namespace maths;

		MayaCamera::MayaCamera(const maths::mat4& projectionMatrix)
			: Camera(projectionMatrix)
		{
			// Sensible defaults
			m_PanSpeed = 0.0015f;
			m_RotationSpeed = 0.002f;
			m_ZoomSpeed = 0.2f;

			m_Position = vec3(0.0f, 25.0f, -25.0f);
			m_Rotation = vec3(90.0f, 0.0f, 0.0f);

			m_FocalPoint = vec3::Zero();
			m_Distance = m_Position.Distance(m_FocalPoint);

			m_Yaw = 3.0f * RD_PI / 4.0f;
			m_Pitch = RD_PI / 4.0f;
		}

		void MayaCamera::Focus()
		{
			Input::GetInputManager()->SetMouseCursor(1);
		}

		void MayaCamera::Update()
		{
			if (Input::IsKeyPressed(RD_KEY_ALT))
			{
				const vec2& mouse = Input::GetMousePosition();
				vec2 delta = mouse - m_InitialMousePosition;
				m_InitialMousePosition = mouse;

				if (Input::IsMouseButtonPressed(RD_MOUSE_MIDDLE))
					MousePan(delta);
				else if (Input::IsMouseButtonPressed(RD_MOUSE_LEFT))
					MouseRotate(delta);
				else if (Input::IsMouseButtonPressed(RD_MOUSE_RIGHT))
					MouseZoom(delta.y);
			}

			// MouseZoom(window->GetMouseScrollPosition().y);

			m_Position = CalculatePosition();

			Quaternion orientation = GetOrientation();
			m_Rotation = orientation.ToEulerAngles() * (180.0f / RD_PI);

			m_ViewMatrix = mat4::Translate(vec3(0, 0, 1)) * mat4::Rotate(orientation.Conjugate()) * mat4::Translate(-m_Position);
		}

		void MayaCamera::MousePan(const maths::vec2& delta)
		{
			m_FocalPoint += -GetRightDirection() * delta.x * m_PanSpeed * m_Distance;
			m_FocalPoint += GetUpDirection() * delta.y * m_PanSpeed * m_Distance;
		}

		void MayaCamera::MouseRotate(const maths::vec2& delta)
		{
			float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
			m_Yaw += yawSign * delta.x * m_RotationSpeed;
			m_Pitch += delta.y * m_RotationSpeed;
		}

		void MayaCamera::MouseZoom(float delta)
		{
			m_Distance -= delta * m_ZoomSpeed;
			if (m_Distance < 1.0f)
			{
				m_FocalPoint += GetForwardDirection();
				m_Distance = 1.0f;
			}
		}

		vec3 MayaCamera::GetUpDirection()
		{
			return Quaternion::Rotate(GetOrientation(), vec3::YAxis());
		}

		vec3 MayaCamera::GetRightDirection()
		{
			return Quaternion::Rotate(GetOrientation(), vec3::XAxis());
		}

		vec3 MayaCamera::GetForwardDirection()
		{
			return Quaternion::Rotate(GetOrientation(), -vec3::ZAxis());
		}

		vec3 MayaCamera::CalculatePosition()
		{
			return m_FocalPoint - GetForwardDirection() * m_Distance;
		}

		Quaternion MayaCamera::GetOrientation()
		{
			return Quaternion::RotationY(-m_Yaw) * Quaternion::RotationX(-m_Pitch);
		}

	}
}