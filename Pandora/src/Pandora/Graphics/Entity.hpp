#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/Mesh.hpp"
#include "Pandora/Graphics/Texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

namespace Pandora {

    class Entity
    {
    public:
        Entity(const char* filepath, const char* texturepath);
        Entity(const Ref<Mesh>& mesh, const char* texturepath);
        Entity(const Ref<Mesh>& mesh, const Ref<Texture2D>& texture);

        const glm::mat4& GetModelMatrix() const { return m_Model; }

        const glm::vec3& GetScale() const { return m_Scale; }
        void SetScale(float scale) { m_Scale = glm::vec3{scale}; CalculateModelMatrix(); }
        void SetScale(const glm::vec3& scale) { m_Scale = scale; CalculateModelMatrix(); }

        void SetPosition(const glm::vec3& position) { m_Position = position; CalculateModelMatrix(); }
        const glm::vec3& GetPosition() const { return m_Position; }

        void AddRotation(float angle, const glm::vec3& axis) { m_Rotation = glm::angleAxis(glm::radians(angle), axis) * m_Rotation; CalculateModelMatrix(); }
        const glm::quat& GetRotation() const { return m_Rotation; }

        const Ref<Mesh>& GetMesh() const { return m_Mesh; }
        const Ref<Texture2D>& GetTexture() const { return m_Texture; }

    protected:
        void CalculateModelMatrix();
    protected:
        Ref<Mesh> m_Mesh;
        Ref<Texture2D> m_Texture;
        
        glm::mat4 m_Model;

        glm::vec3 m_Position;
        glm::vec3 m_Scale;
        glm::quat m_Rotation;
    };
}