#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "Shader.hpp"

namespace
{
    unsigned int CompileShader(const GLchar *source, GLenum shaderType)
{
    auto programID = glCreateShader(shaderType);
    GLCall(glShaderSource(programID, 1, &source, nullptr));
    GLCall(glCompileShader(programID));
    
    int  success;
    char infoLog[512];
    // Check Vertex Shader
    GLCall(glGetShaderiv(programID, GL_COMPILE_STATUS, &success));
    if ( !success ){
        GLCall(glGetShaderInfoLog(programID, 512, NULL, infoLog));
        throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
    }
    
    return programID;
    
};

unsigned int LinkProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID)
{
    auto ID =glCreateProgram();
    GLCall(glAttachShader(ID,vertexShaderID));
    GLCall(glAttachShader(ID,fragmentShaderID));
    GLCall(glLinkProgram(ID));
    
    return ID;
};


}


Shader::Shader()
{
    
}

unsigned int Shader::LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
    auto VertexShaderCode = IO_Util::getFile(vertex_file_path);
    auto FragmentShaderCode = IO_Util::getFile(fragment_file_path);
    
    unsigned int vertexShaderID = CompileShader(VertexShaderCode.c_str(),GL_VERTEX_SHADER);
    unsigned int fragmentShaderID = CompileShader(FragmentShaderCode.c_str(),GL_FRAGMENT_SHADER);
    
    ProgramID = LinkProgram(vertexShaderID, fragmentShaderID);
    
    GLCall(glDeleteShader(vertexShaderID));
    GLCall(glDeleteShader(fragmentShaderID));
    
    return ProgramID;
}


void Shader::use() const
{
    GLCall(glUseProgram(ProgramID));
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ProgramID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ProgramID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ProgramID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ProgramID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ProgramID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ProgramID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ProgramID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    
}

unsigned int Shader::getUniform(std::string name)
{
    return glGetUniformLocation(ProgramID,name.c_str());
};

Shader::~Shader()
{
    glDeleteProgram(ProgramID);
}
