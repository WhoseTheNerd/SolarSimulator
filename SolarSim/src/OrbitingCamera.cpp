#include "OrbitingCamera.hpp"

namespace SolarSim {

    constexpr float CAM_FOV = 45.0f;
    constexpr float CAM_NEAR = 0.1f;
    constexpr float CAM_FAR = 100'000.0f;
    
    OrbitingCamera::OrbitingCamera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up)
        : m_ProjectionMatrix(glm::perspective(glm::radians(CAM_FOV), 1280.0f/720.0f, CAM_NEAR, CAM_FAR)), 
          m_Eye(eye), m_LookAt(lookAt), m_UpVector(up), m_ScreenWidth(1280.0f), m_ScreenHeight(720.0f)
    {
        UpdateViewMatrix();
    }

    void OrbitingCamera::OnUpdate(Pandora::Timestep ts)
    {
        
    }

    void OrbitingCamera::OnEvent(Pandora::Event& e)
    {
        Pandora::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<Pandora::MouseMovedEvent>(PD_BIND_EVENT_FN(SolarSim::OrbitingCamera::OnMouseMoved));
        dispatcher.Dispatch<Pandora::MouseScrolledEvent>(PD_BIND_EVENT_FN(SolarSim::OrbitingCamera::OnMouseScrolled));
        dispatcher.Dispatch<Pandora::WindowResizeEvent>(PD_BIND_EVENT_FN(SolarSim::OrbitingCamera::OnWindowResized));
    }

    void OrbitingCamera::SetCameraView(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up)
    {
        m_Eye = eye;
        m_LookAt = lookAt;
        m_UpVector = up;
        UpdateViewMatrix();
    }

    void OrbitingCamera::UpdateViewMatrix()
    {
        m_ViewMatrix = glm::lookAt(m_Eye, m_LookAt, m_UpVector);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    bool OrbitingCamera::OnMouseMoved(Pandora::MouseMovedEvent& e)
    {
        static float lastMouseX = 0.0f, lastMouseY = 0.0f;

        if (m_FirstMouseEvent) {
            m_FirstMouseEvent = false;
            lastMouseX = e.GetX();
            lastMouseY = e.GetY();
        }

        glm::vec4 position(m_Eye.x, m_Eye.y, m_Eye.z, 1.0f);
        glm::vec4 pivot(m_LookAt.x, m_LookAt.y, m_LookAt.z, 1.0f);

        float deltaAngleX = (2 * M_PI / m_ScreenWidth); // a movement from left to right = 2*PI = 360 deg
        float deltaAngleY = (M_PI / m_ScreenHeight);  // a movement from top to bottom = PI = 180 deg

        float cosAngle = glm::dot(GetViewDir(), m_UpVector);
        if (cosAngle * glm::sign(deltaAngleY) > 0.99f)
            deltaAngleY = 0;

        float xAngle = (lastMouseX - e.GetX()) * deltaAngleX;
        float yAngle = (lastMouseY - e.GetY()) * deltaAngleY;

        // step 2: Rotate the camera around the pivot point on the first axis.
        glm::mat4x4 rotationMatrixX(1.0f);
        rotationMatrixX = glm::rotate(rotationMatrixX, xAngle, m_UpVector);
        position = (rotationMatrixX * (position - pivot)) + pivot;

        // step 3: Rotate the camera around the pivot point on the second axis.
        glm::mat4x4 rotationMatrixY(1.0f);
        rotationMatrixY = glm::rotate(rotationMatrixY, yAngle, GetRightVector());
        glm::vec3 finalPosition = (rotationMatrixY * (position - pivot)) + pivot;

        // Update the camera view (we keep the same lookat and the same up vector)
        SetCameraView(finalPosition, m_LookAt, m_UpVector);

        // Update the mouse position for the next rotation
        lastMouseX = e.GetX(); 
        lastMouseY = e.GetY();

        return false;
    }

    bool OrbitingCamera::OnMouseScrolled(Pandora::MouseScrolledEvent& e)
    {
        m_ZoomLevel += -e.GetYOffset() * 0.1f;
        PD_INFO("{}", m_ZoomLevel);

        const glm::vec3 v1 = m_Eye - m_LookAt;
        const glm::vec3 v2 = m_ZoomLevel * v1;

        m_Eye = m_LookAt + v2;

        UpdateViewMatrix();

        return false;   
    }

    bool OrbitingCamera::OnWindowResized(Pandora::WindowResizeEvent& e)
    {
        m_ScreenWidth = e.GetWidth();
        m_ScreenHeight = e.GetHeight();
        m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
        m_ProjectionMatrix = glm::perspective(glm::radians(CAM_FOV), m_AspectRatio, CAM_NEAR, CAM_FAR);
        UpdateViewMatrix();
        return false;
    }
}