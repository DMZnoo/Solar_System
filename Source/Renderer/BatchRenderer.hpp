//
//  ParticleRenderer.hpp
//  Portfolio_Jinwoo_Lee
//
//  Created by JINWOO LEE on 13/06/20.
//

#ifndef ParticleRenderer_hpp
#define ParticleRenderer_hpp
#include "../Model/BatchModel.hpp"
#include "../Control/Camera.hpp"
#include "../Shader/ModelShader.hpp"
#include "../Texture/BaseTexture.hpp"
class BatchRenderer
{
public:
    BatchRenderer(std::string path,std::string type);
    float randomFloat(float a, float b);
    void render( Camera &camera);
private:
    BatchModel m_model;
    BaseTexture m_texture;
    glm::mat4 model;
    ModelShader m_shader;
    std::string typeModel;
    float movingSpeed,spinningSpeed,angleChange,instances;
    struct Random
    {
        float radius;
        float speed;
        float tilt;
    };
    std::vector<Random> loc;
    std::vector<glm::mat4> mats;

};

#endif /* ParticleRenderer_hpp */
