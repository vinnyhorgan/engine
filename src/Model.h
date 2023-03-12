#pragma once

#include "Shader.h"
#include "Mesh.h"

#include <string>
#include <vector>

class Model {
public:
    std::vector<Mesh> meshes;

    Model();
    void load(const std::string& path);
    void draw(Shader& shader);
};
