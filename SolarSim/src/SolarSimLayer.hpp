#pragma once

#include <Pandora.hpp>

namespace SolarSim {

    class SolarSimLayer : public Pandora::Layer
    {
    public:
        SolarSimLayer();
        virtual ~SolarSimLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Pandora::Timestep ts) override;
        virtual void OnRender() override;
        virtual void OnEvent(Pandora::Event& event);
    private:
        bool OnKeyPressed(Pandora::KeyPressedEvent& e);
    private:
        Pandora::Ref<Pandora::VertexArray> m_VAO;
        Pandora::Ref<Pandora::Shader> m_Shader;
        Pandora::Ref<Pandora::Texture2D> m_Texture;

        Pandora::OrthographicCameraController m_CameraController;
    };

}