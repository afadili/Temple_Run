#ifndef _LIB_IMPORT_MODEL_IMAC_LSM
#define _LIB_IMPORT_MODEL_IMAC_LSM
/*#pragma once

#include <glimac/SDLWindowManager.hpp>
#include <iostream>
#include <glimac/glm.hpp>
#include <random>
#include <algorithm>
#include <queue>


//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type; 
    aiString path;
};

class Meshes {
    private:
        unsigned int vao, vbo, ebo;
        void setupMesh();
    public:
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
        std::vector<Texture> _textures;

        Meshes(std::vector<Vertex> vert, std::vector<unsigned int> ind, std::vector<Texture> tex):_vertices(vert),_indices(ind),_textures(tex){
            setupMesh();
        };
        void draw() const;
};
class Model{
    private:
        std::vector<Meshes> meshes;
        std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Meshes processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    public:
        Model(std::string path){
            loadModel(path);
        }
        void draw() const;
};

#endif*/