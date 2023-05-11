#include "Renderer3D.hpp"

#include "Pandora/Core/ColorUtil.hpp"

#include "Pandora/Graphics/Shader.hpp"
#include "Pandora/Graphics/RenderCommand.hpp"

namespace Pandora {

    struct Renderer3DStorage
    {
        Ref<Shader> ShaderProgram;
        Scope<Skybox> SkyboxObj;
    };

    static Scope<Renderer3DStorage> s_Data;

    void Renderer3D::Init(const char* shaderpath)
    {
        s_Data = CreateScope<Renderer3DStorage>();
        s_Data->ShaderProgram = Shader::Create(shaderpath);
        s_Data->ShaderProgram->SetUniform("u_UseTextures", 0);
        s_Data->ShaderProgram->SetUniform("u_LightPos", glm::vec3{-2.0f, 12.0f, 12.0f});
        s_Data->ShaderProgram->SetUniform("u_LightColor", Pandora::FromHex("#D3D3D3"));
    }

    void Renderer3D::Shutdown()
    {
    }

    void Renderer3D::BeginScene(const PerspectiveCamera& camera)
    {
        s_Data->ShaderProgram->Bind();
        s_Data->ShaderProgram->SetUniform("u_ViewProjection", camera.GetViewProjectionMatrix());

        glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        s_Data->SkyboxObj->GetShader()->SetUniform("view", view);
        s_Data->SkyboxObj->GetShader()->SetUniform("projection", camera.GetProjectionMatrix());

        RenderCommand::Clear();
    }

    void Renderer3D::EndScene()
    {
        RenderCommand::SetDepthFunction(DepthFunctionMode::LessEqual);

        s_Data->SkyboxObj->GetCubeMap()->Bind();
        s_Data->SkyboxObj->GetShader()->Bind();
        RenderCommand::DrawIndexed(s_Data->SkyboxObj->GetMesh());

        RenderCommand::SetDepthFunction(DepthFunctionMode::Less);
    }

    void Renderer3D::DrawEntity(const Ref<Entity>& entity)
    {
        entity->GetTexture()->Bind();
        s_Data->ShaderProgram->SetUniform("u_UseTextures", 1);
        s_Data->ShaderProgram->SetUniform("u_Texture", 0);
        s_Data->ShaderProgram->SetUniform("u_Model", entity->GetModelMatrix());

        RenderCommand::DrawIndexed(entity->GetMesh());
    }


    void Renderer3D::SetSkybox(Scope<Skybox> skybox)
    {
        s_Data->SkyboxObj = std::move(skybox);
    }
}