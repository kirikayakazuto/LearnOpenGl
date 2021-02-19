//
//  Mesh.hpp
//  GLFW_OpenGL
//
//  Created by hortor on 2021/2/18.
//  Copyright © 2021 hortor. All rights reserved.
//



#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Shader.hpp"

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    
    void draw(Shader shader);
    
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};

#endif /* Mesh_hpp */
