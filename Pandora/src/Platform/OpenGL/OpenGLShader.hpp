#pragma once

#define USE_CACHING 1

#include "Pandora/Graphics/Shader.hpp"

#if USE_CACHING
#include <unordered_map>
#endif

namespace Pandora {


    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const char* shaderSource);
        virtual ~OpenGLShader();

        virtual void Bind() const override;

        virtual void SetUniform(const char* name, uint32_t value) override;
        virtual void SetUniform(const char* name, const glm::vec2& value) override;
        virtual void SetUniform(const char* name, const glm::vec3& value) override;
        virtual void SetUniform(const char* name, const glm::vec4& value) override;
        virtual void SetUniform(const char* name, const glm::mat4& matrix) override;
    private:
        std::pair<std::string, std::string> ParseShaderFile(const char* file);
        int GetShaderUniformLocation(const char* name) const;
        int CreateShader(const char* vertexSource, const char* fragmentSource);
        int CompileShader(const char* source, uint32_t type);
    private:
        uint32_t m_ProgramHandle;

        #if USE_CACHING
        mutable std::unordered_map<std::string, int> m_UniformLocations;
        #endif
    };
}