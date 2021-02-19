//
//  Mesh.cpp
//  GLFW_OpenGL
//
//  Created by hortor on 2021/2/18.
//  Copyright © 2021 hortor. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
}

void Mesh::setupMesh() {
    glad_glGenVertexArrays(1, &VAO);
    glad_glGenBuffers(1, &VBO);
    glad_glGenBuffers(1, &EBO);
    
    glad_glBindVertexArray(VAO);
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // 顶点位置
    glad_glEnableVertexAttribArray(0);
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    // 顶点法线
    glad_glEnableVertexAttribArray(1);
    glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    // 纹理坐标
    glad_glEnableVertexAttribArray(2);
    glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    
    glad_glBindVertexArray(0);
}

void Mesh::draw(Shader shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i=0; i<textures.size(); i++) {
        glad_glActiveTexture(GL_TEXTURE0 + i);
        string number;
        string name = textures[i].type;
        if(name == "texture_diffuse") number = std::to_string(diffuseNr ++);
        else if(name == "texture_specular") number = std::to_string(specularNr ++);
        
        shader.setFloat(("material." + name + number).c_str(), i);
        glad_glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glad_glActiveTexture(GL_TEXTURE0);
    
    glad_glBindVertexArray(VAO);
    glad_glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);
    glad_glBindVertexArray(0);
}


