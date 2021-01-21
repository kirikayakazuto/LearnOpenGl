//
//  Shader.cpp
//  GLFW_OpenGL
//
//  Created by hortor on 2021/1/14.
//  Copyright © 2021 hortor. All rights reserved.
//

#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std:: cout << "Error shader file not succes" << std::endl;
    }
    
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    vertex = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertex, 1, &vShaderCode, NULL);
    glad_glCompileShader(vertex);
    glad_glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glad_glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std:: cout << "ERROR shader vertex compilation failed" << infoLog << std:: endl;
    }
    
    fragment = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(fragment, 1, &fShaderCode, NULL);
    glad_glCompileShader(fragment);
    glad_glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glad_glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std:: cout << "ERROR shader fragment compilation failed" << infoLog << std:: endl;
    }
    
    ID = glad_glCreateProgram();
    glad_glAttachShader(ID, vertex);
    glad_glAttachShader(ID, fragment);
    glad_glLinkProgram(ID);
    
    glad_glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glad_glDeleteShader(vertex);
    glad_glDeleteShader(fragment);
}


void Shader::use() {
    glad_glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glad_glUniform1i(glad_glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glad_glUniform1i(glad_glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glad_glUniform1f(glad_glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glad_glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) const {
    glad_glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glad_glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
