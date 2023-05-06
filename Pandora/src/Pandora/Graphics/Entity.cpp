#include "Entity.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Pandora {

    Entity::Entity(const char* filepath, const char* texturepath)
        : m_Mesh(CreateRef<Mesh>(filepath)), m_Texture(Texture2D::Create(texturepath)), m_Model(1.0f), m_Position(0.0f), m_Scale(1.0f), m_Rotation(0.0f)
    {
    }

    Entity::Entity(const Ref<Mesh>& mesh, const char* texturepath)
        : m_Mesh(mesh), m_Texture(Texture2D::Create(texturepath)), m_Model(1.0f), m_Position(0.0f), m_Scale(1.0f), m_Rotation(0.0f)
    {
    }

    void Entity::CalculateModelMatrix()
    {
        m_Model = glm::identity<glm::mat4>();
        m_Model = glm::translate(m_Model, m_Position);
        m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.x), {1.0f, 0.0f, 0.0f});
        m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.y), {0.0f, 1.0f, 0.0f});
        m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.z), {0.0f, 0.0f, 1.0f});
        m_Model = glm::scale(m_Model, m_Scale);
    }

}