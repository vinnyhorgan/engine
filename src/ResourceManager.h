#pragma once

#include "Shader.h"
#include "Texture.h"

#include <map>

class ResourceManager {
public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture> textures;

    static Shader loadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name);
    static Shader getShader(const std::string& name);
    static Texture loadTexture(const std::string& path, const std::string& name);
    static Texture getTexture(const std::string& name);
    static void dispose();

private:
    ResourceManager() { }
};
