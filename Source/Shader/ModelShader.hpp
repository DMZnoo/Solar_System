//
//  PlatformShader.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 4/05/20.
//

#ifndef ModelShader_hpp
#define ModelShader_hpp
#include "Shader.hpp"
class ModelShader : public Shader
{
public:
    ModelShader();
    ModelShader(std::string type);
    void SetProjectionMatrix(glm::mat4 proj);
    void SetViewMatrix(glm::mat4 view);
    void SetModelMatrix(glm::mat4 model);
    void SetLight();
private:
    std::string modelType;
};


#endif /* PlatformShader_hpp */
