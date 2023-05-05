#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/Mesh.hpp"
#include "Pandora/Graphics/Texture.hpp"

#include <glm/glm.hpp>

namespace Pandora {

    class Entity
    {
    public:
        Entity(const char* filepath, const char* texturepath);

        const glm::mat4& GetModelMatrix() const { return m_Model; }

        const glm::vec3& GetScale() const { return m_Scale; }
        void SetScale(float scale) { m_Scale = glm::vec3{scale}; CalculateModelMatrix(); }
        void SetScale(const glm::vec3& scale) { m_Scale = scale; CalculateModelMatrix(); }

        void SetPosition(const glm::vec3& position) { m_Position = position; CalculateModelMatrix(); }
        const glm::vec3& GetPosition() const { return m_Position; }

        void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; CalculateModelMatrix(); }
        const glm::vec3& GetRotation() const { return m_Rotation; }

        const Ref<Mesh>& GetMesh() const { return m_Mesh; }
        const Ref<Texture2D>& GetTexture() const { return m_Texture; }

    private:
        void CalculateModelMatrix();
    private:
        Ref<Mesh> m_Mesh;
        Ref<Texture2D> m_Texture;
        
        glm::mat4 m_Model;

        glm::vec3 m_Position;
        glm::vec3 m_Scale;
        glm::vec3 m_Rotation;
    };
}