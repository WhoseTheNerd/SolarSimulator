#include "Entity.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Pandora {

    Entity::Entity(const char* filepath, const char* texturepath)
        : m_Mesh(CreateRef<Mesh>(filepath)), m_Texture(Texture2D::Create(texturepath)), m_Model(1.0f), m_Position(0.0f), m_Scale(1.0f), m_Rotation(1.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    Entity::Entity(const Ref<Mesh>& mesh, const char* texturepath)
        : m_Mesh(mesh), m_Texture(Texture2D::Create(texturepath)), m_Model(1.0f), m_Position(0.0f), m_Scale(1.0f), m_Rotation(1.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    Entity::Entity(const Ref<Mesh>& mesh, const Ref<Texture2D>& texture)
        : m_Mesh(mesh), m_Texture(texture), m_Model(1.0f), m_Position(0.0f), m_Scale(1.0f), m_Rotation(1.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    void Entity::CalculateModelMatrix()
    {
        m_Model = glm::identity<glm::mat4>();
        m_Model = glm::translate(m_Model, m_Position);
        m_Model *= glm::toMat4(m_Rotation);
        m_Model = glm::scale(m_Model, m_Scale);
    }

    void Entity::AddRotation(const glm::vec3& eulerAngle)
    {
        m_Rotation *= glm::quat(glm::radians(eulerAngle));
        CalculateModelMatrix(); 
    }

    void Entity::AddRotation(float angle, const glm::vec3& axis)
    { 
        m_Rotation *= glm::angleAxis(glm::radians(angle), axis);
        CalculateModelMatrix(); 
    }
}
