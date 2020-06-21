//
//  PlatformRenderer.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 4/05/20.
//

#ifndef ModelRenderer_hpp
#define ModelRenderer_hpp
#include "../Shader/ModelShader.hpp"
#include "../Control/Camera.hpp"
#include "../Model/Model.hpp"
#include "../Texture/BaseTexture.hpp"
#include "../Utility/IO_Util.hpp"
class ModelRenderer : public NonCopyable{
  public:
    ModelRenderer(std::string path,std::string type);
    void render( Camera &camera);
    void setLocation(glm::mat4 location);
    glm::mat4 transferLocation();
    float randomFloat(float a, float b);
  private:
    Model m_model;
    glm::mat4 model;
    ModelShader m_shader;
    BaseTexture m_texture;
    unsigned int diffuse_n,specular_n,normal_n,height_n;
    std::string typeModel;
    float movingSpeed,spinningSpeed,angleChange;
    float angle,radius,x,z,scale,closestX,closestZ;
    float orbitalDistance;
    
    struct AsteroidData
    {
        float randSpeed;
        float randDistance;
        float randtilt;
        float randSpin;
        float randScale;
    };
    std::vector<AsteroidData> asteroids;
    std::vector<glm::mat4> asteroidMats;
    unsigned int asteroidCount;
    glm::vec3 camPos,camDisplacement;
    std::string followingObj;
    float randomPlacement;
    
};



#endif /* ModelRenderer_hpp */
