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

        bool operator==(const Vertex& other) const {
            return Position == other.Position && TexCoords == other.TexCoords;
        }

        static Pandora::BufferLayout GetBufferLayout() {
            return {
                { Pandora::ShaderDataType::Float3, "a_Position" },
                { Pandora::ShaderDataType::Float2, "a_UV" },
                { Pandora::ShaderDataType::Float3, "a_Normal" },
            };
        }
    };
}

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

namespace std {
        template<> struct hash<Pandora::Vertex> {
        size_t operator()(Pandora::Vertex const& vertex) const {
            size_t seed = hash<glm::vec3>()(vertex.Position);
            hash_combine(seed, vertex.TexCoords);
            hash_combine(seed, vertex.Normal);
            return seed;
        }
    };
}