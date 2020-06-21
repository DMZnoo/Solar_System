//
//  ParticleRenderer.cpp
//  Portfolio_Jinwoo_Lee
//
//  Created by JINWOO LEE on 13/06/20.
//

#include "BatchRenderer.hpp"

BatchRenderer::BatchRenderer(std::string path,std::string type)
:m_model(0.015f,3,2),m_shader(type)
{
    m_texture.LoadTexture(IO_Util::concat(path).c_str());
    m_shader.use();
    typeModel = type;
    model = glm::mat4(1.0f);
    m_model.drop();
    m_model.buildVertices();
    m_model.bind();
    movingSpeed = 5.f;
    spinningSpeed = 0.f;
    angleChange = 1.f;
    Random random;
    instances = 20000;
    for (int i = 0; i < instances; i++)
    {
        random.radius = randomFloat(329.f, 478.f);
        random.speed = randomFloat(0.01f, 1.f);
        random.tilt  = randomFloat(0.f,20.f);
        loc.push_back(random);
        model = glm::mat4(1);
        mats.push_back(model);
    }
    //SBO is just another buffer object (Stream Buffer Object) that is initially empty and will be populated during rendering.
    //Unlike normal shaders, there will be an extra attrib-pointers that increments for every instance (by using attrib-divisors). This will allow us to render lots of similar objects with one render call.
    m_model.addSBO(instances,mats);
    
}

void BatchRenderer::render(Camera &camera) {
    angleChange++;
    //0.02f = 1 day
    spinningSpeed+=0.02f;
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    GLCall(glDepthFunc(GL_LESS));
    m_shader.use();
    m_shader.SetProjectionMatrix(camera.getProjMatrix());
    m_shader.SetViewMatrix(camera.getViewMatrix());
    model = glm::mat4(1.f);
    m_texture.Bind2DTexture();
    m_model.bindVAO();
    m_model.bindVBO();
    m_shader.SetLight();
    //update matrices
    for(int i = 0; i < instances; i++)
    {
        float radius = 1.f + (loc[i].radius * 0.05f);
        float angle =  angleChange  * movingSpeed * loc[i].speed;
        float x = radius * sin(PI * 2 * (i+angle) / 360);
        float z = radius * cos(PI * 2 * (i+angle) / 360);
        mats[i] = glm::mat4(1);
        mats[i] = glm::rotate(mats[i], glm::radians(loc[i].tilt),glm::vec3(0,0,1));
        mats[i] = glm::translate(mats[i],glm::vec3(x,0,z));
        mats[i] = glm::rotate(mats[i], glm::radians(loc[i].tilt),glm::vec3(0,0,1));
        mats[i] = glm::rotate(mats[i], spinningSpeed * loc[i].speed, glm::vec3(0,1,0));

    }
    //bind this new updated matrices to the SBO
    m_model.bindSBO(instances,mats);
    //draw instances
    GLCall(glDrawElementsInstanced(GL_TRIANGLES, m_model.getRendererInfo().indicesCount, GL_UNSIGNED_INT, 0, instances));
        
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_CULL_FACE);
    
    
    
}

float BatchRenderer::randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
