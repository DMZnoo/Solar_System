//
//  Controller.cpp
//
//  Created by JINWOO LEE on 11/05/20.
//

#include "Controller.hpp"
extern GLFWwindow* window;

Controller::Controller()
{
    xTarget = glm::pi<float>();
    yTarget = 0.0f;
    speed = 0.005f;
    movementSpeed = 20.0f;
    xpos = width / 2;
    ypos = height / 2;
    landing = false;
    m_position = glm::vec3(5, 0, 5);
    m_direction = glm::vec3(0,0,0);
}






glm::vec3 Controller::updateDir() {
    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    deltaTime = float(currentTime - lastTime);
    
    glfwGetCursorPos(window, &xpos, &ypos);
    
    // Compute new orientation
    xTarget += speed * float(width/2 - xpos );
    yTarget += speed * float(height/2 - ypos );
    

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    m_direction = glm::vec3 (
        cos(yTarget) * sin(xTarget),
        sin(yTarget),
        cos(yTarget) * cos(xTarget)
    );
    
    
    // Right vector
    right = glm::vec3(
        sin(xTarget - glm::pi<float>()/2.0f),
        0,
        cos(xTarget - glm::pi<float>()/2.0f)
    );
    
    // Up vector
    up = glm::cross( right, m_direction);
    

    
    
    
    lastTime = currentTime;
    
    return m_direction;
    
}
glm::vec3 Controller::updateKeyboardInput()
{
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            if(glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE)
            {
                LOCK_ON_OBJECT = !LOCK_ON_OBJECT;
            }
        }
        // Move forward
        if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
            
            m_position += m_direction * deltaTime * movementSpeed;
        }
        // Move backward
        if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
            m_position -= m_direction * deltaTime * movementSpeed;
        }
        // Move left
        if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
            m_position -= right * deltaTime * movementSpeed;
        }
        // Move right
        if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
            m_position += right * deltaTime * movementSpeed;
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            m_position += glm::vec3(0,1,0) * deltaTime * movementSpeed;
        }
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
         m_position -= glm::vec3(0,1,0) * deltaTime * movementSpeed;
        }
    
        
        
    
        
    
    return m_position;
    
        
}

glm::vec3 Controller::getUpVector() { 
    return up;
}

void Controller::setLocation(glm::vec3 newLocation) { 
    m_position = newLocation;
}

void Controller::setDirection(glm::vec3 newDirection) { 
    m_direction = newDirection;
}






