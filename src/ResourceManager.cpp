#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

Shader ResourceManager::loadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name) {
    Shader shader;
    shader.load(vertexPath, fragmentPath);
    shaders[name] = shader;
    return shaders[name];
}

Shader ResourceManager::getShader(const std::string& name) {
    return shaders[name];
}

Texture ResourceManager::loadTexture(const std::string& path, const std::string& name) {
    Texture texture;
    texture.load(path);
    textures[name] = texture;
    return textures[name];
}

Texture ResourceManager::getTexture(const std::string& name) {
    return textures[name];
}

void ResourceManager::dispose() {
    for (auto iter : shaders) {
        iter.second.dispose();
    }

    for (auto iter : textures) {
        iter.second.dispose();
    }
}
