#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/Buffer.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pandora {
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec2 TexCoords;
        glm::vec3 Normal;
        glm::vec3 Color;

        bool operator==(const Vertex& other) const {
            return Position == other.Position && TexCoords == other.TexCoords;
        }

        static Pandora::BufferLayout GetBufferLayout() {
            return {
                { Pandora::ShaderDataType::Float3, "a_Position" },
                { Pandora::ShaderDataType::Float2, "a_UV" },
                { Pandora::ShaderDataType::Float3, "a_Normal" },
                { Pandora::ShaderDataType::Float3, "a_Color" },
            };
        }
    };
}

namespace std {
        template<> struct hash<Pandora::Vertex> {
        size_t operator()(Pandora::Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.Position) ^
                   (hash<glm::vec2>()(vertex.TexCoords) << 1)));
        }
    };
}