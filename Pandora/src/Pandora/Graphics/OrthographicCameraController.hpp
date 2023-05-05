#pragma once

#include "Pandora/Core/Base.hpp"
#include "Pandora/Core/Timestep.hpp"
#include "Pandora/Events/Event.hpp"
#include "Pandora/Events/ApplicationEvent.hpp"
#include "Pandora/Events/MouseEvent.hpp"
#include "Pandora/Graphics/OrthographicCamera.hpp"

namespace Pandora {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

		void SetTranslationSpeed(float speed) { m_CameraTranslationSpeed = speed; }
		float GetTranslationSpeed() const { return m_CameraTranslationSpeed; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; // In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };
}