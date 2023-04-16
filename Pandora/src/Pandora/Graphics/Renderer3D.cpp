#include "Renderer3D.hpp"

#include "Pandora/Core/ColorUtil.hpp"

#include "Pandora/Graphics/Shader.hpp"
#include "Pandora/Graphics/RenderCommand.hpp"

namespace Pandora {

    struct Renderer3DStorage
    {
        Ref<Shader> ShaderProgram;
    };

    static Renderer3DStorage* s_Data;

    void Renderer3D::Init()
    {
        s_Data = new Renderer3DStorage();
        s_Data->ShaderProgram = Shader::Create("SolarSim/assets/basic.shader");
        s_Data->ShaderProgram->SetUniform("u_UseTextures", 0);
        s_Data->ShaderProgram->SetUniform("u_LightPos", glm::vec3{-2.0f, 12.0f, 12.0f});
        s_Data->ShaderProgram->SetUniform("u_LightColor", Pandora::FromHex("#D3D3D3"));
    }

    void Renderer3D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer3D::BeginScene(const PerspectiveCamera& camera)
    {
        s_Data->ShaderProgram->Bind();
        s_Data->ShaderProgram->SetUniform("u_ViewProjection", camera.GetViewProjectionMatrix());

        RenderCommand::Clear();
    }

    void Renderer3D::EndScene()
    {

    }

    void Renderer3D::DrawEntity(const Ref<Entity>& entity)
    {
        s_Data->ShaderProgram->SetUniform("u_UseTextures", 0);
        s_Data->ShaderProgram->SetUniform("u_Model", entity->GetModelMatrix());

        RenderCommand::DrawIndexed(entity->GetMesh());
    }

    void Renderer3D::DrawEntity(const Ref<Entity>& entity, Ref<Texture2D> texture)
    {
        texture->Bind();
        s_Data->ShaderProgram->SetUniform("u_UseTextures", 1);
        s_Data->ShaderProgram->SetUniform("u_Texture", 0);
        s_Data->ShaderProgram->SetUniform("u_Model", entity->GetModelMatrix());

        RenderCommand::DrawIndexed(entity->GetMesh());
    }
}