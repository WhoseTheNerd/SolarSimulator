#pragma once

#include "Pandora/Core/Base.hpp"

#include <glm/glm.hpp>

namespace Pandora {

    class Shader
    {
    public:
        Shader() = default;
        virtual ~Shader() = default;

        virtual void Bind() const = 0;

        virtual void SetUniform(const char* name, uint32_t value) = 0;
        virtual void SetUniform(const char* name, const glm::vec2& value) = 0;
        virtual void SetUniform(const char* name, const glm::vec3& value) = 0;
        virtual void SetUniform(const char* name, const glm::vec4& value) = 0;
        virtual void SetUniform(const char* name, const glm::mat4& matrix) = 0;

        static Scope<Shader> Create(const char* shaderSource);
    };
}