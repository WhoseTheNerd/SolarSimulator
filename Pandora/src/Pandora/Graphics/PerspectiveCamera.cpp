#include "PerspectiveCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Pandora {

    PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio)
        : m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f)), m_ViewMatrix(1.0f)
    {
        RecalculateViewMatrix();
    }

    void PerspectiveCamera::SetProjection(float fov, float aspectRatio)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void PerspectiveCamera::RecalculateViewMatrix()
    {
        glm::vec3 front;
        front.x = std::cos(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));
        front.y = std::sin(glm::radians(m_Pitch));
        front.z = std::sin(glm::radians(m_Yaw)) * std::cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);

        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));

        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}