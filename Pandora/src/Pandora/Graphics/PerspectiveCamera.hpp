#pragma once

#include "Pandora/Core/Base.hpp"

#include <glm/glm.hpp>

namespace Pandora {

    class PerspectiveCamera
    {
    public:
        PerspectiveCamera(float fov, float aspectRatio);

        void SetProjection(float fov, float aspectRatio);

        const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

        float GetYaw() const { return m_Yaw; }
        void SetYaw(float yaw) { m_Yaw = yaw; RecalculateViewMatrix(); }

        float GetPitch() const { return m_Pitch; }
        void SetPitch(float pitch) { m_Pitch = pitch; RecalculateViewMatrix(); }

        glm::vec3 GetFront() const { return m_Front; }
        glm::vec3 GetUp() const { return m_Up; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_Front = {0.0f, 0.0f, -1.0f};
        glm::vec3 m_Up;
        glm::vec3 m_WorldUp = {0.0f, 1.0f, 0.0f};
        glm::vec3 m_Right;

        float m_Yaw;
        float m_Pitch;
    };
}