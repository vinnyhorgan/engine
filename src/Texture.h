#pragma once

#include <string>

class Texture {
public:
    unsigned int id;
    std::string type;
    std::string path;

    Texture();
    void load(const std::string& path);
    void bind();
    void dispose();
};
