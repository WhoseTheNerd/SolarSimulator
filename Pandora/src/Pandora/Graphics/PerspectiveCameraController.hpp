#pragma once 

#include "Pandora/Core/Base.hpp"
#include "Pandora/Core/Timestep.hpp"
#include "Pandora/Events/Event.hpp"
#include "Pandora/Events/MouseEvent.hpp"
#include "Pandora/Events/ApplicationEvent.hpp"
#include "Pandora/Graphics/PerspectiveCamera.hpp"

namespace Pandora {

    class PerspectiveCameraController
    {
    public:
        PerspectiveCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		PerspectiveCamera m_Camera;

		glm::vec3 m_CameraPosition = { -0.344802f, 0.0f, 2.33222f };
        float m_CameraYaw = -90.0f;
        float m_CameraPitch = 0.0f;
		float m_CameraTranslationSpeed = 5.0f;
    };
}