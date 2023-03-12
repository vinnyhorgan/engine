#pragma once

#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <string>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    // Overload operator== for Vertex struct
    bool operator==(const Vertex& other) const {
        return position == other.position && normal == other.normal && texCoords == other.texCoords;
    }
};

// Hash function for Vertex struct
namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.position) ^
                (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
                (hash<glm::vec2>()(vertex.texCoords) << 1);
        }
    };
}

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(Shader& shader);
};
