#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>

Texture::Texture() {
    glGenTextures(1, &id);
}

void Texture::load(const std::string& path) {
    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (data) {
        GLenum format;

        if (channels == 1) {
            format = GL_RED;
        } else if (channels == 3) {
            format = GL_RGB;
        } else if (channels == 4) {
            format = GL_RGBA;
        } else {
            std::cout << "Error loading texture: " << path << std::endl;
            stbi_image_free(data);
            return;
        }

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Error loading texture: " << path << std::endl;
        stbi_image_free(data);
    }
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::dispose() {
    glDeleteTextures(1, &id);
}
