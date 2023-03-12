#include "Model.h"

#include <glad/glad.h>
#include <stb_image.h>
#include <tiny_obj_loader.h>

#include <iostream>
#include <unordered_map>

Model::Model() {

}

void Model::load(const std::string& path) {
    std::string directory = path.substr(0, path.find_last_of('/'));

    tinyobj::ObjReaderConfig readerConfig;
    readerConfig.mtl_search_path = directory;
    readerConfig.triangulate = true;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, readerConfig)) {
        if (!reader.Error().empty()) {
            std::cout << "Error loading model: " << reader.Error() << std::endl;
        }

        return;
    }

    if (!reader.Warning().empty()) {
        std::cout << "Warning loading model: " << reader.Warning() << std::endl;
    }

    const tinyobj::attrib_t& attrib = reader.GetAttrib();
    const std::vector<tinyobj::shape_t>& shapes = reader.GetShapes();
    const std::vector<tinyobj::material_t>& materials = reader.GetMaterials();

    std::cout << "Number of vertices = " << (int)attrib.vertices.size() / 3 << std::endl;
    std::cout << "Number of normals = " << (int)attrib.normals.size() / 3 << std::endl;
    std::cout << "Number of texcoords = " << (int)attrib.texcoords.size() / 2 << std::endl;
    std::cout << "Number of shapes = " << (int)shapes.size() << std::endl;
    std::cout << "Number of materials = " << (int)materials.size() << std::endl;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    std::unordered_map<Vertex, unsigned int> uniqueVertices = {};

    for (const tinyobj::shape_t& shape : shapes) {
        for (const tinyobj::index_t& index : shape.mesh.indices) {
            Vertex vertex = {};

            vertex.position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.normal = {
                attrib.normals[3 * index.normal_index + 0],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2]
            };

            vertex.texCoords = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = (unsigned int)vertices.size();
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }

    for (const tinyobj::material_t& material : materials) {
        if (!material.diffuse_texname.empty()) {
            Texture texture;
            texture.load(directory + "/" + material.diffuse_texname);
            texture.type = "texture_diffuse";
            texture.path = material.diffuse_texname;
            textures.push_back(texture);
        }

        if (!material.specular_texname.empty()) {
            Texture texture;
            texture.load(directory + "/" + material.specular_texname);
            texture.type = "texture_specular";
            texture.path = material.specular_texname;
            textures.push_back(texture);
        }
    }

    meshes.push_back(Mesh(vertices, indices, textures));
}

void Model::draw(Shader& shader) {
    for (Mesh& mesh : meshes) {
        mesh.draw(shader);
    }
}
