#include "Pandora/Graphics/PerspectiveCameraController.hpp"

#include "Pandora/Core/Input.hpp"

namespace Pandora {

    PerspectiveCameraController::PerspectiveCameraController(float aspectRatio)
        : m_AspectRatio(aspectRatio), m_Camera(45.0f, aspectRatio)
    {
        m_Camera.SetYaw(m_CameraYaw);
        m_Camera.SetPitch(m_CameraPitch);
    }

    void PerspectiveCameraController::OnUpdate(Timestep ts)
    {
        constexpr float G = 9.81f;
        constexpr float JUMP_HEIGHT = 2.0f;
        static bool jumping = false;

        float y = m_CameraPosition.y;
        if (Input::IsKeyPressed(Key::A))
		{
            m_CameraPosition -= glm::normalize(glm::cross(m_Camera.GetFront(), m_Camera.GetUp())) * (m_CameraTranslationSpeed * ts);
		}
		else if (Input::IsKeyPressed(Key::D))
		{
            m_CameraPosition += glm::normalize(glm::cross(m_Camera.GetFront(), m_Camera.GetUp())) * (m_CameraTranslationSpeed * ts);
		}

		if (Input::IsKeyPressed(Key::W))
		{
            m_CameraPosition += (m_CameraTranslationSpeed * ts) * m_Camera.GetFront();
		}
		else if (Input::IsKeyPressed(Key::S))
		{
            m_CameraPosition -= (m_CameraTranslationSpeed * ts) * m_Camera.GetFront();
		}
        m_CameraPosition.y = y;

        if (m_CameraPosition.y <= 0.0f) {
            jumping = false;
        }

        if (Input::IsKeyPressed(Key::Space) && m_CameraPosition.y == 0.0f)
        {
            jumping = true;
        }
        
        if (jumping) {
            m_CameraPosition.y += G * ts;
            if (m_CameraPosition.y > JUMP_HEIGHT) {
                jumping = false;
            }
        } else {
            m_CameraPosition.y -= G * ts;
        }

        if (m_CameraPosition.y < 0.0f) {
            m_CameraPosition.y = 0.0f;
        }

        m_Camera.SetPosition(m_CameraPosition);
    }

    void PerspectiveCameraController::OnEvent(Event& e)
    {
		EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseMovedEvent>(PD_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
		dispatcher.Dispatch<WindowResizeEvent>(PD_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
    }

    void PerspectiveCameraController::OnResize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_Camera.SetProjection(45.0f, m_AspectRatio);
    }

    bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
    {
        static float lastX = 0.0f, lastY = 0.0f;

        constexpr float mouseSensitivity = 0.1f;

        float xoffset = e.GetX() - lastX;
        float yoffset = lastY - e.GetY();

        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        lastX = e.GetX();
        lastY = e.GetY();

        m_CameraYaw += xoffset;
        m_CameraPitch += yoffset;

        if (m_CameraPitch > 89.0f) {
            m_CameraPitch = 89.0f;
        } else if (m_CameraPitch < -89.0f) {
            m_CameraPitch = -89.0f;
        }

        m_Camera.SetYaw(m_CameraYaw);
        m_Camera.SetPitch(m_CameraPitch);

        return false;
    }

    bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        OnResize(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
        return false;
    }
}