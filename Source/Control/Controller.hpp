//
//  Controller.hpp
//
//  Created by JINWOO LEE on 11/05/20.
//

#ifndef Controller_hpp
#define Controller_hpp
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <GLFW/glfw3.h>
extern bool LOCK_ON_OBJECT;
extern unsigned int width, height;
class Controller
{
public:
    Controller();
    virtual glm::vec3 updateDir();
    virtual glm::vec3 updateKeyboardInput();
    void setLocation(glm::vec3 newLocation);
    void setDirection(glm::vec3 newDirection);
    glm::vec3 getUpVector();
private:
    float xTarget,yTarget,speed,movementSpeed;
    double xpos, ypos;
    
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 m_direction,m_position;
    float deltaTime;
    float landing;
};

#endif /* Controller_hpp */
