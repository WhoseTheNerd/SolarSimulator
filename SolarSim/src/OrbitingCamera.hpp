#pragma once

#include <Pandora.hpp>

namespace SolarSim {

    class OrbitingCamera
    {
    public:
        OrbitingCamera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up);

        void OnUpdate(Pandora::Timestep ts);
		void OnEvent(Pandora::Event& e);

        void SetCameraView(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up);

        glm::vec3 GetViewDir() const { return -glm::transpose(m_ViewMatrix)[2]; }
        glm::vec3 GetRightVector() const { return glm::transpose(m_ViewMatrix)[0]; }

        void SetTarget(const glm::vec3& target) { m_LookAt = target; UpdateViewMatrix(); }
        void SetPosition(const glm::vec3& pos) { m_Eye = pos; UpdateViewMatrix(); }

        glm::vec3* GetPosition() { return &m_Eye; }

        void SetFirstMouseEvent(bool state) { m_FirstMouseEvent = state; }

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    private:
        void UpdateViewMatrix();

		bool OnMouseMoved(Pandora::MouseMovedEvent& e);
		bool OnWindowResized(Pandora::WindowResizeEvent& e);
    private:
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Eye; // Camera position
        glm::vec3 m_LookAt; // Point that camera looks at
        glm::vec3 m_UpVector; // Orientation of the camera

        float m_ScreenWidth;
        float m_ScreenHeight;
        float m_AspectRatio;

        bool m_FirstMouseEvent = true;
    };
}