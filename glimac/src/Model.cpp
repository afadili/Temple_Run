#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
/*#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Sphere.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glimac/Image.hpp>
#include <random>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <glimac/Model.hpp>

using namespace glimac;

void Model::draw() const{
    for(unsigned int i = 0;i < meshes.size();i++)
    {
        meshes[i].draw();
    }
}

void Meshes::setupMesh(){
    glGenVertexArrays(1, &vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(Vertex), &_vertices[0],GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof(unsigned int), &_indices[0],GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex,Normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,3,GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex,TexCoords));

    glBindVertexArray(vao);
}

void Meshes::draw() const{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for(unsigned int i = 0;i < _textures.size();i++){
        glActiveTexture(GL_TEXTURE0+i);

        std::string number;
        std::string name = _textures[i].type;

        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES,_indices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(vao);
}

unsigned int TextureFromFile(std::string file,std::string dir){
        unsigned int tex;
   		std::unique_ptr<Image> img = loadImage(dir+"/"+file);

        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D,tex);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img->getWidth(),img->getHeight(),0,GL_RGBA,GL_FLOAT,img->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D,0);
        return tex;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0;i < mat->GetTextureCount(type);i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture tex;
        tex.id = TextureFromFile(str.C_Str(), directory);
        tex.type = typeName;
        tex.path = str;
        textures.push_back(tex);
    }
    return textures;
}

Meshes Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for(unsigned int i = 0;i < mesh->mNumVertices;i++)
    {
        Vertex vert;
        vert.Position = glm::vec3(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z);
        vert.Normal = glm::vec3(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z);

        if(mesh->mTextureCoords[0])
            vert.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        else
            vert.TexCoords = glm::vec2(0.0f,0.0f);
        vertices.push_back(vert);
    }

    for(unsigned int i = 0;i < mesh->mNumFaces;i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0;j < face.mNumIndices;j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(mat, aiTextureType_DIFFUSE,"texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadMaterialTextures(mat, aiTextureType_SPECULAR,"texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    }

    return Meshes(vertices, indices, textures);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0;i < node->mNumMeshes;i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for(unsigned int i = 0;i < node->mNumChildren;i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::loadModel(std::string path){
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::"<< import.GetErrorString()<<std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}*/