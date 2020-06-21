//
//  ModelRenderer.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 4/05/20.
//

#include "ModelRenderer.hpp"
extern std::string ROOT;
ModelRenderer::ModelRenderer(std::string path, std::string type)
:m_shader(type){
    if(type != "asteroid")
        m_model.loadModel(IO_Util::concat(path.c_str()).c_str(),GL_STATIC_DRAW);
    else
        m_model.loadModel(IO_Util::concat(path.c_str()).c_str(),GL_STREAM_DRAW); //stream draw since the object will be updated and re-drawn alot
    m_shader.use();
    typeModel = type;
    model = glm::mat4(1.0f);
    movingSpeed = 10.f;
    spinningSpeed = 0.f;
    angleChange = 1.f;
    scale = 0.1f;
    orbitalDistance = 0.05f;
    followingObj = typeModel;
    camDisplacement = glm::vec3(-10);
    closestX = 100;
    closestZ = 100;
    if(type == "asteroid")
    {
        asteroidCount = 30;
        m_texture.LoadTexture(IO_Util::concat("asteroid/asteroid_diff.jpg").c_str());
        for(int i = 0; i < asteroidCount; i++)
        {
            AsteroidData asteroidData;
            asteroidData.randSpeed = randomFloat(0.01f, 1.f);
            asteroidData.randDistance = randomFloat(329.f, 478.f);
            asteroidData.randtilt = randomFloat(0.f,20.f);
            asteroidData.randSpin = randomFloat(1.f,10.f);
            asteroidData.randScale = randomFloat(0.001f,0.005f);
            asteroids.push_back(asteroidData);
            model = glm::mat4(1);
            asteroidMats.push_back(model);
        }
        randomPlacement = 0 + (rand() % 50);
        m_model.addSBO(asteroidCount,asteroidMats);
        
    }

    
};

void ModelRenderer::render(Camera &camera) {
    camPos = camera.getCamPos();
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
    if(typeModel == "space")
    {
        glDisable(GL_CULL_FACE);
        GLCall(glDepthFunc(GL_LEQUAL));
        glFrontFace(GL_CW);
        model = glm::mat4(1.f);
        model = glm::scale( model, glm::vec3( 200.f ) );
        m_shader.SetLight();
    }
    else if(typeModel == "sun")
    {
        model = glm::mat4(1.f);
        model = glm::rotate(model, glm::radians(7.25f),glm::vec3(0,0,1));
        //sun's 1 rotation = 24 earth rotation
        model = glm::rotate(model, spinningSpeed*0.024f, glm::vec3(0,1,0));
        //the sun is 109 times bigger than the earth - it's scaled differently for visibility
        model = glm::scale( model, glm::vec3(109.f * 0.01f));
    }
    else if(typeModel == "earth")
    {
        model = glm::mat4(1.f);
        angle = 0.006f * angleChange  * movingSpeed;
        
        //distance from the sun = 147.1 million km.
        //1.f is the offset from the sun's core to the edge
        radius = 1.f + (147.1f * orbitalDistance);
        x = radius * sin(PI * 2 * angle / 360);
        z = radius * cos(PI * 2 * angle / 360);
       
        model = glm::translate( model, glm::vec3( x, 0, z) );
        
        camDisplacement = glm::vec3((x-camPos.x),0,(z-camPos.z));
        camera.addDisplacement(typeModel,camDisplacement,radius,angle);

            
        //Earth's axial tilt = 23.44 degrees
        model = glm::rotate(model, glm::radians(23.44f),glm::vec3(0,0,1));
        model = glm::rotate(model, spinningSpeed, glm::vec3(0,1,0));
        //planets will be based on the earth's size = 1.f
        model = glm::scale(model,glm::vec3(1.f * scale));
        m_shader.SetLight();
    } else if (typeModel == "moon")
    {
        //moon's rotates around the earth in 27 days and 13 degrees a day.
        angle = 0.006f * angleChange*0.13f  * movingSpeed*0.27f;
        
        //distance from the sun = 384,400 km.
        //0.05f is the offset from the earth's core to the edge
        radius = 0.05f + (384.4f * 0.01f);
        x = radius * sin(PI * 2 * angle / 360);
        z = radius * cos(PI * 2 * angle / 360);
        //Moon's orbital tilt 5 degrees
        model = glm::rotate(model, glm::radians(5.f),glm::vec3(0,0,1));
        model = glm::translate( model, glm::vec3( x, 0, z) );
        //Moon's axial tilt =  1.5 degrees
        model = glm::rotate(model, glm::radians(1.5f),glm::vec3(0,0,1));
        //moon's 1 rotation = 27 earth rotation
        model = glm::rotate(model, spinningSpeed*0.27f, glm::vec3(0,1,0));
        //the Moon is approximately 27% the size of the Earth - it's scaled differently for visibility
        model = glm::scale(model,glm::vec3(0.1f));
        m_shader.SetLight();
    }
else if (typeModel == "mercury")
    {
        model = glm::mat4(1.f);
        //The mercury rotates the sun 4 times faster than the earth (1 rotation in 88 earth days)
        angle = 0.08f * angleChange * movingSpeed * 4.f;
        //distance from the sun 57.91 million km.
        //1.f is the offset from the sun's core to the edge
        radius = 1.f+(57.91f * orbitalDistance);
        x = radius * sin(PI * 2 * angle / 360);
        z = radius * cos(PI * 2 * angle / 360);
        //Mercury's orbital tilt 7 degrees
        model = glm::rotate(model, glm::radians(7.f),glm::vec3(0,0,1));
        model = glm::translate( model, glm::vec3( x, 0, z) );

        camDisplacement = glm::vec3((x-camPos.x),0,(z-camPos.z));
        camera.addDisplacement(typeModel,camDisplacement,radius,angle);
        
        //Mercury's axial tilt =  0.03 degrees
        model = glm::rotate(model, glm::radians(0.03f),glm::vec3(0,0,1));
        
        //Mercury's 1 rotation = 58.8 earth rotations
        model = glm::rotate(model, spinningSpeed*0.0588f, glm::vec3(0,1,0));
        
        //Mercury is 38% of the size of the earth.
        model = glm::scale(model,glm::vec3(1.f * scale * 0.38f));
//        model = glm::scale(model,glm::vec3(1.f * 0.1f));
        m_shader.SetLight();
    } else if (typeModel == "venus")
    {
        model = glm::mat4(1.f);
        //Venus rotates every 224 days.
        angle = 0.07f * angleChange * movingSpeed * 0.614f;
        //distance from the sun = 108.2 million km.
        //1.f is the offset from the sun's core to the edge
        radius = 1.f+(108.2f * orbitalDistance);
        x = radius * sin(PI * 2 * angle / 360);
        z = radius * cos(PI * 2 * angle / 360);
        //Venus's orbital tilt 3.39 degrees
        model = glm::rotate(model, glm::radians(3.39f),glm::vec3(0,0,1));
        model = glm::translate( model, glm::vec3( x, 0, z) );
        
        camDisplacement = glm::vec3((x-camPos.x),0,(z-camPos.z));
        camera.addDisplacement(typeModel,camDisplacement,radius,angle);
        
        //Venus's axial tilt =  2.64 degrees
        model = glm::rotate(model, glm::radians(2.64f),glm::vec3(0,0,1));
        
        //Venus's 1 rotation = 243 earth rotations
        model = glm::rotate(model, -spinningSpeed*0.243f, glm::vec3(0,1,0));
        
        //Venus is 95% of the size of the earth.
        model = glm::scale(model,glm::vec3(1.f * scale * 0.95f));
//        model = glm::scale(model,glm::vec3(1.f * 0.1f));
        m_shader.SetLight();
    }
    else if (typeModel == "mars")
    {
        model = glm::mat4(1.f);
        angle = 0.05f * angleChange  * movingSpeed * 0.5f;
         
         //distance from the sun = 227.9 million km.
         //1.f is the offset from the sun's core to the edge
         radius = 1.f + (227.9f *orbitalDistance);
         x = radius * sin(PI * 2 * angle / 360);
         z = radius * cos(PI * 2 * angle / 360);

         //Mars' orbital tilt =  1.85 degrees
        model = glm::rotate(model, glm::radians(1.85f),glm::vec3(0,0,1));
         model = glm::translate( model, glm::vec3( x, 0, z) );
        
        camDisplacement = glm::vec3((x-camPos.x),0,(z-camPos.z));
        camera.addDisplacement(typeModel,camDisplacement,radius,angle);

         //Mars' axial tilt = 25.19 degrees
         model = glm::rotate(model, glm::radians(25.19f),glm::vec3(0,0,1));
         model = glm::rotate(model, spinningSpeed, glm::vec3(0,1,0));
         //Mars is 53% of the size of the earth.
        model = glm::scale(model,glm::vec3(1.f * scale * 0.53f));
         m_shader.SetLight();
    } else if (typeModel == "jupiter")
    {
        model = glm::mat4(1.f);
        //Jupiter rotates around the sun every 12 years. 365/4332 = 0.084
        angle = 0.045f * angleChange  * movingSpeed * 0.084f;
         
         //distance from the sun = 778.5 million km.
         //1.f is the offset from the sun's core to the edge
         radius = 1.f + (778.5f *orbitalDistance);
         x = radius * sin(PI * 2 * angle / 360);
         z = radius * cos(PI * 2 * angle / 360);

         //Jupiter's orbital tilt =  1.3 degrees
         model = glm::rotate(model, glm::radians(1.3f),glm::vec3(0,0,1));
         model = glm::translate( model, glm::vec3( x, 0, z) );
        
        
        
        camDisplacement = glm::vec3((x-camPos.x),0,(z-camPos.z));
        camera.addDisplacement(typeModel,camDisplacement,radius,angle);
        
        
//        camera.addDisplacement(typeModel, glm::vec3(x,0,z));
         //Jupiter's axial tilt = 3.13 degrees
        model = glm::rotate(model, glm::radians(3.13f),glm::vec3(0,0,1));
        //Jupiter rotates every 9 hrs 19 minutes (earth term)
        model = glm::rotate(model, spinningSpeed*2.66f, glm::vec3(0,1,0));
         //Jupiter is 1120% of the size of the earth.
        model = glm::scale(model,glm::vec3(1.f * scale * 11.2f));
         m_shader.SetLight();
    } else if (typeModel == "saturn")
    {
        model = glm::mat4(1.f);
        //Saturn rotates around the sun every 29.4 years. 365/10731 = 0.034
        angle = 0.040f * angleChange  * movingSpeed * 0.034f;
         
         //distance from the sun = 1.434 billion km.
         //1.f is the offset from the sun's core to the edge
        radius = 1.f + (1434.f *orbitalDistance);
        x = radius * sin(PI * 2 * angle / 360);
        z = radius * cos(PI * 2 * angle / 360);

         //Saturn's orbital tilt =  2.64 degrees
         model = glm::rotate(model, glm::radians(2.64f),glm::vec3(0,0,1));
         model = glm::translate( model, glm::vec3( x, 0, z) );
        
        
        camDisplacement = glm::vec3((x-camPos.x),0,(z-camPos.z));
        camera.addDisplacement(typeModel,camDisplacement,radius,angle);
        
         //Saturn's axial tilt = 26.73 degrees
        model = glm::rotate(model, glm::radians(26.73f),glm::vec3(0,0,1));
        //Saturn rotates every 10 earth hours
        model = glm::rotate(model, spinningSpeed*2.4f, glm::vec3(0,1,0));
        
//        model = glm::rotate(model, glm::radians(90.f),glm::vec3(0,0,1));

         //Saturn is 945% of the size of the earth.
        model = glm::scale(model,glm::vec3(1.f * scale * .0945f));
         m_shader.SetLight();
    } else if (typeModel == "uranus")
    {
        model = glm::mat4(1.f);
        //Uranus rotates around the sun every 84 years. 365/30660 = 0.012
        angle = 0.035f * angleChange  * movingSpeed * 0.012f;
         
        //distance from the sun = 2.871 billion km.
        //1.f is the offset from the sun's core to the edge
        radius = 1.f + (2871.f *orbitalDistance);
        x = radius * sin(PI * 2 * angle / 360);
        z = radius * cos(PI * 2 * angle / 360);

        //Uranus' orbital tilt =  0.77 degrees
        model = glm::rotate(model, glm::radians(0.77f),glm::vec3(0,0,1));
        model = glm::translate( model, glm::vec3( x, 0, z) );
        
        camDisplacement = glm::vec3((x-camPos.x),0,(z-camPos.z));
        camera.addDisplacement(typeModel,camDisplacement,radius,angle);
        
        //Uranus' axial tilt = 97.8 degrees
        model = glm::rotate(model, glm::radians(97.8f),glm::vec3(0,0,1));
        //Uranus rotates every 17 earth hours
        model = glm::rotate(model, spinningSpeed*1.4f, glm::vec3(0,1,0));
        //Uranus is 400% of the size of the earth.
        model = glm::scale(model,glm::vec3(1.f * scale * .04f));
         m_shader.SetLight();
    } else if (typeModel == "neptune")
    {
        model = glm::mat4(1.f);
        //Neptune rotates around the sun every 164 years. 365/59860 = 0.006
        angle = 0.040f * angleChange  * movingSpeed * 0.006f;
         
        //distance from the sun = 4.495 billion km.
        //1.f is the offset from the sun's core to the edge
        radius = 1.f + (4495.f *orbitalDistance);
        x = radius * sin(PI * 2 * angle / 360);
        z = radius * cos(PI * 2 * angle / 360);

        //Neptune's orbital tilt =  1.77 degrees
        model = glm::rotate(model, glm::radians(1.77f),glm::vec3(0,0,1));
        model = glm::translate( model, glm::vec3( x, 0, z) );
        
        camDisplacement = glm::vec3((x-camPos.x),0,(z-camPos.z));
        camera.addDisplacement(typeModel,camDisplacement,radius,angle);
        
        
        //Neptune's axial tilt = 28 degrees
        model = glm::rotate(model, glm::radians(28.f),glm::vec3(0,0,1));
        //Neptune rotates every 16 earth hours
        model = glm::rotate(model, spinningSpeed*1.5f, glm::vec3(0,1,0));
        //Neptune is 388% of the size of the earth.
        model = glm::scale(model,glm::vec3(1.f * scale * .0388f));
         m_shader.SetLight();
    }
        if(LOCK_ON_OBJECT)
        {
            
            camDisplacement = camera.returnSmallest();
            std::cout << glm::to_string(camera.returnSmallest()) <<std::endl;
            if(abs(camDisplacement.x) < 10.f || abs(camDisplacement.z) < 10.f)
            {
                
                camera.cameraPosUpdate(glm::vec3(camera.getData().x,camera.getData().y,0));
                camera.cameraDirUpdate(glm::vec3(camDisplacement.x,0,camDisplacement.z));
            } else
            {
                
                LOCK_ON_OBJECT = !LOCK_ON_OBJECT;
            }

        }
    m_shader.SetModelMatrix(model);
    if(typeModel == "asteroid")
    {
            //update matrices = updating the position/rotation/tilt of all asteroids
            for(int n = 0; n < asteroidCount;n++)
            {
                m_shader.SetLight();
                m_texture.Bind2DTexture();
                m_model.bindVAO();
                m_model.bindVBO();
                asteroidMats[n] = glm::mat4(1.f);
                //Astroid would all have different speeds
                angle =  angleChange  * movingSpeed * asteroids[n].randSpeed;

                //distance from the sun = 329-478 million km.
                //1.f is the offset from the sun's core to the edge
                radius = 1.f + (asteroids[n].randDistance * orbitalDistance);
                x = radius * sin(PI * 2 * (n+angle) / 360);
                z = radius * cos(PI * 2 * (n+angle) / 360);

                //random orbital tilt
                asteroidMats[n] = glm::rotate(asteroidMats[n], glm::radians(asteroids[n].randtilt),glm::vec3(0,0,1));
                asteroidMats[n] = glm::translate(asteroidMats[n],glm::vec3(x,0,z));
                //random axial tilt
                asteroidMats[n] = glm::rotate(asteroidMats[n], glm::radians(asteroids[n].randtilt),glm::vec3(0,0,1));

                asteroidMats[n] = glm::rotate(asteroidMats[n], spinningSpeed*asteroids[n].randSpin, glm::vec3(0,1,0));
                asteroidMats[n] = glm::scale(asteroidMats[n],glm::vec3(1.f * scale * asteroids[n].randScale));
            }
            //bind the stream buffer
            m_model.bindSBO(asteroidCount,asteroidMats);
            //draw instances
            GLCall(glDrawElementsInstanced(GL_TRIANGLES,m_model.getIndicesCount(), GL_UNSIGNED_INT, 0, asteroidCount));
        
    }
    else
    {
        for(unsigned int i = 0; i < m_model.getModelInfo().size(); i++)
        {
            
            diffuse_n = 1;specular_n = 1; normal_n = 1; height_n = 1;
            for(unsigned int n = 0; n < m_model.getModelInfo()[i].textures.size();n++)
            {
                GLCall(glActiveTexture(GL_TEXTURE0 + n));
                std::string num;
                std::string type = m_model.getModelInfo()[i].textures[n].type;
                if(type == "texture_diffuse")
                    num = std::to_string(diffuse_n++);
                else if (type == "texture_specular")
                    num = std::to_string(specular_n++);
                else if (type == "texture_normal")
                    num = std::to_string(normal_n++);
                else
                    num = std::to_string(height_n++);
                m_shader.setInt((type+num).c_str(),i);
                
                glBindTexture(GL_TEXTURE_2D,m_model.getModelInfo()[i].textures[n].textID);
                
            }
            
            GLCall(glBindVertexArray(m_model.getRendererInfo().vao_list[i]));
            if(typeModel == "path")
            {
                m_shader.SetLight();
                //Earth
                model = glm::mat4(1.f);
                model = glm::translate( model, glm::vec3( 0, -0.5f, 0) );
                model = glm::scale(model,glm::vec3(1.f+(147.1f*orbitalDistance)));
                m_shader.SetModelMatrix(model);
                GLCall(glDrawElements(GL_TRIANGLES,m_model.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
                

                //Mercury
                model = glm::mat4(1.f);
                model = glm::translate( model, glm::vec3( 0, -0.5f, 0) );
                model = glm::scale(model,glm::vec3(1.f+(57.91f*orbitalDistance)));
                model = glm::rotate(model, glm::radians(7.f),glm::vec3(0,0,1));
                m_shader.SetModelMatrix(model);
                GLCall(glDrawElements(GL_TRIANGLES,m_model.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));

                
                //Venus
                model = glm::mat4(1.f);
                model = glm::translate( model, glm::vec3( 0, -0.5f, 0) );
                model = glm::scale(model,glm::vec3(1.f+(108.2f*orbitalDistance)));
                model = glm::rotate(model, glm::radians(3.39f),glm::vec3(0,0,1));
                m_shader.SetModelMatrix(model);
                GLCall(glDrawElements(GL_TRIANGLES,m_model.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
                
                //Mars
                model = glm::mat4(1.f);
                model = glm::translate( model, glm::vec3( 0, -0.5f, 0) );
                model = glm::scale(model,glm::vec3(1.f+(227.9f*orbitalDistance)));
                m_shader.SetModelMatrix(model);
                GLCall(glDrawElements(GL_TRIANGLES,m_model.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
                
                
                //Jupiter
                model = glm::mat4(1.f);
                model = glm::translate( model, glm::vec3( 0, -0.5f, 0) );
                model = glm::scale(model,glm::vec3(1.f+(778.5f *orbitalDistance)));
                m_shader.SetModelMatrix(model);
                GLCall(glDrawElements(GL_TRIANGLES,m_model.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
                
                //Saturn
                model = glm::mat4(1.f);
                model = glm::translate( model, glm::vec3( 0, -0.5f, 0) );
                model = glm::scale(model,glm::vec3(1.f+(1434.f *orbitalDistance)));
                m_shader.SetModelMatrix(model);
                GLCall(glDrawElements(GL_TRIANGLES,m_model.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
                
                //Uranus
                model = glm::mat4(1.f);
                model = glm::translate( model, glm::vec3( 0, -1.f, 0) );
                float scaleGrid = 1.f+(2871.f *orbitalDistance);
                model = glm::scale(model,glm::vec3(scaleGrid,0.1f,scaleGrid));
                m_shader.SetModelMatrix(model);
                GLCall(glDrawElements(GL_TRIANGLES,m_model.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
                
                //Neptune
                model = glm::mat4(1.f);
                model = glm::translate( model, glm::vec3( 0, -1.f, 0) );
                scaleGrid = 1.f+(4495.f *orbitalDistance);
                model = glm::scale(model,glm::vec3(scaleGrid,0.1f,scaleGrid));
                m_shader.SetModelMatrix(model);
                GLCall(glDrawElements(GL_TRIANGLES,m_model.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
                

            }
            else
            {
                GLCall(glDrawElements(GL_TRIANGLES,m_model.getModelInfo()[i].indices.size(),GL_UNSIGNED_INT,0));
            }

    }
    
        glDisable(GL_CULL_FACE);

        glBindVertexArray(0);
    }

    
    
};
void ModelRenderer::setLocation(glm::mat4 location) {
   
    model = location;
}
glm::mat4 ModelRenderer::transferLocation() {
    return model;
}
float ModelRenderer::randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
