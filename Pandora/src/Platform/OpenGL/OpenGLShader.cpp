#include "OpenGLShader.hpp"

#include <sstream>
#include <fstream>

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

namespace Pandora {

    Scope<Shader> Shader::Create(const char* shaderSource)
    {
        return CreateScope<OpenGLShader>(shaderSource);
    }

    OpenGLShader::OpenGLShader(const char* shaderSource)
        : m_ProgramHandle(0)
    {
        auto[vertexSource, fragmentSource] = ParseShaderFile(shaderSource);
        m_ProgramHandle = CreateShader(vertexSource.c_str(), fragmentSource.c_str());
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ProgramHandle);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ProgramHandle);
    }

    void OpenGLShader::SetUniform(const char* name, uint32_t value)
    {
        glProgramUniform1i(m_ProgramHandle, GetShaderUniformLocation(name), value);
    }

    void OpenGLShader::SetUniform(const char* name, const glm::vec2& value)
    {
        glProgramUniform2f(m_ProgramHandle, GetShaderUniformLocation(name), value.x, value.y);
    }

    void OpenGLShader::SetUniform(const char* name, const glm::vec3& value)
    {
        glProgramUniform3f(m_ProgramHandle, GetShaderUniformLocation(name), value.x, value.y, value.z);
    }

    void OpenGLShader::SetUniform(const char* name, const glm::vec4& value)
    {
        glProgramUniform4f(m_ProgramHandle, GetShaderUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::SetUniform(const char* name, const glm::mat4& matrix)
    {
        glProgramUniformMatrix4fv(m_ProgramHandle, GetShaderUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    std::pair<std::string, std::string> OpenGLShader::ParseShaderFile(const char* file)
    {
        std::ifstream stream(file);

        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;

        while(std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                } else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
            } else {
                ss[static_cast<size_t>(type)] << line << '\n';
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    int OpenGLShader::GetShaderUniformLocation(const char* name) const
    {
        return glGetUniformLocation(m_ProgramHandle, name);
    }

    int OpenGLShader::CreateShader(const char* vertexSource, const char* fragmentSource)
    {
        uint32_t program = glCreateProgram();
        uint32_t vs = CompileShader(vertexSource, GL_VERTEX_SHADER);
        uint32_t fs = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        int result;
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

            char* message = new char[length];

            glGetProgramInfoLog(program, length, &length, message);

            PD_CORE_ERROR("Failed to link program!\n{0}", message);

            delete[] message;
            return 0;
        }

        glValidateProgram(program);
        glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

            char* message = new char[length];

            glGetProgramInfoLog(program, length, &length, message);

            PD_CORE_ERROR("Shader program validation failed!\n{0}", message);

            delete[] message;
            return 0;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    int OpenGLShader::CompileShader(const char* source, uint32_t type)
    {
        uint32_t shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        int result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            char* message = new char[length];

            glGetShaderInfoLog(shader, length, &length, message);

            PD_CORE_ERROR("Failed to compile {0} shader:\n{1}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);

            delete[] message;

            return 0;
        }

        return shader;
    }

}