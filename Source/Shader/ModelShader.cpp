//
//  PlatformShader.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 4/05/20.
//

#include "ModelShader.hpp"
ModelShader::ModelShader()
: Shader()
{
    Shader::LoadShaders("GLSL/ModelVertexShader.glsl", "GLSL/ModelFragmentShader.glsl");
};
ModelShader::ModelShader(std::string type)
: Shader()
{
    modelType = type;
    if(modelType == "sun" || modelType == "path")
        Shader::LoadShaders("GLSL/SunVertexShader.glsl", "GLSL/SunFragmentShader.glsl");
    else if(modelType == "space")
        Shader::LoadShaders("GLSL/DirectionalLightVertexShader.glsl", "GLSL/DirectionalLightFragmentShader.glsl");
    else if (modelType == "asteroid")
        Shader::LoadShaders("GLSL/InstancedModelVertexShader.glsl", "GLSL/ModelFragmentShader.glsl");
    else if (modelType == "belt")
        Shader::LoadShaders("GLSL/FoggyVertexShader.glsl", "GLSL/FoggyFragmentShader.glsl");
    else
        Shader::LoadShaders("GLSL/ModelVertexShader.glsl", "GLSL/ModelFragmentShader.glsl");
};
void ModelShader::SetProjectionMatrix(glm::mat4 proj) {
    Shader::setMat4("projection",proj);
};

void ModelShader::SetViewMatrix(glm::mat4 view) {
    Shader::setMat4("view",view);
};

void ModelShader::SetModelMatrix(glm::mat4 model) {
    Shader::setMat4("model",model);
};


void ModelShader::SetLight()
{
    
    if(modelType != "sun")
    {
        Shader::setVec3("light.position",0,0,0);
        if(modelType == "uranus")
            {
                Shader::setVec3("light.ambient", 5.f, 5.f, 5.f );
                Shader::setVec3("light.diffuse" , 100.f, 100.f, 100.f );
            }
        else if(modelType == "neptune")
            {
                Shader::setVec3("light.ambient", 5.f, 5.f, 5.f );
                Shader::setVec3("light.diffuse" , 200.f, 200.f, 200.f );
            }
        else if(modelType == "belt")
        {
            Shader::setVec3("light.ambient", 2.f, 2.f, 2.f );
            Shader::setVec3("light.diffuse" , 10.f, 10.f, 10.f );
        } else if(modelType == "space")
        {
            Shader::setVec3("light.ambient", 2.f, 2.f, 2.f );
            Shader::setVec3("light.diffuse" , 1.f, 1.f, 1.f );
        } else
        {
            Shader::setVec3("light.ambient", 2.f, 2.f, 2.f );
            Shader::setVec3("light.diffuse" , 20.f, 20.f, 20.f );
        }
        Shader::setVec3("light.specular", 0.0f, 0.0f, 0.0f);
        Shader::setFloat("light.constant", 1.0f );
        Shader::setFloat("light.linear" , 0.02f );
        Shader::setFloat("light.quadratic", 0.006f );

    }

};
