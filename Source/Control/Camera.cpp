//
//  Camera.cpp
//
//  Created by JINWOO LEE on 27/04/20.
//

#include "Camera.hpp"
extern GLFWwindow* window;

Camera::Camera(int width, int height, std::string *array)
{
    Position = glm::vec3(0,0,0);
    i_viewMatrix = glm::mat4(1.0f);
    i_projMatrix = glm::mat4(1.0f);
    
    RotatedAngle = 0.f;
    for(int i =0; i < 8;i++)
    {
        displacements[array[i]] = glm::vec3(100);
        displacementsData[array[i]] = glm::vec3(0);
    }
}

void Camera::update()
{
    float FoV = 45.0f;
    // Projection matrix : 45∞ Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
    i_projMatrix = glm::perspective(
                        glm::radians(FoV), //the amount of "zoom"
                        static_cast<float>(width/height), //Aspect Ratio.
                        0.1f, //near clipping plane
                        1000.0f
    ); //far clipping plane
    
        
        if(!LOCK_ON_OBJECT)
        {
            //free flowing camera
            Direction = controller.updateDir();
            Position = controller.updateKeyboardInput();
            i_viewMatrix = glm::mat4(1.0f);
            i_viewMatrix = glm::lookAt(
                Position,           // Camera's current position
                Position+Direction,     // and looks at this direction
                controller.getUpVector() // up vector of the camera
                );
        }
        else
        {
        //locked into an object
        //this function catches the unlock action (free flow<->locked object)
        controller.updateKeyboardInput();
        i_viewMatrix = glm::mat4(1.0f);
        //the object rotating angle with the offset of 10.f (behind the object)
        float offsetX = radius * sin(glm::radians(RotatedAngle-10.f));
        float offsetZ = radius * cos(glm::radians(RotatedAngle-10.f));
        
        Direction = glm::vec3(offsetX,0,offsetZ);
        Position = Direction;

        //this was done so that when switched to the other (free-to-moveabout) camera, the position would be preserved
        controller.setLocation(Position);

        
        Direction = glm::vec3(
            sin(glm::radians(RotatedAngle+90.f)),
            Direction[1],
            cos(glm::radians(RotatedAngle+90.f))
        );

        
        i_viewMatrix = glm::lookAt(
            Position,           // Camera's current position
            Position+Direction,     // and looks at this direction
            glm::vec3(0,1,0) // up vector of the camera
            );


            

        }
            
    glfwSetCursorPos(window, width/2, height/2);
    
    
}




const glm::mat4& Camera::getViewMatrix()
{
    return i_viewMatrix;
}

const glm::mat4& Camera::getProjMatrix()
{
    return i_projMatrix;
}

void Camera::setViewMatrix(glm::mat4 viewMatrix)
{
    i_viewMatrix = viewMatrix;
}

void Camera::cameraPosUpdate(glm::vec3 pos) {
    radius = pos.x;
    RotatedAngle = pos.y;
}


void Camera::cameraDirUpdate(glm::vec3 dir)
{
    x = dir.x;
    y = dir.y;
    z = dir.z;
    Direction = dir;
}

glm::vec3 Camera::getCamPos()
{
    return Position;
}
glm::vec3 Camera::returnSmallest()
{
    return getMin(displacements);
    

    
};
glm::vec2 Camera::getData()
{
    return data;
}
 void Camera::addDisplacement(std::string type,glm::vec3 disp,float radius, float angle)
{
    displacements[type] = disp;
    displacementsData[type] = glm::vec2(radius,angle);
}
//return the closet planet
glm::vec3 Camera::getMin(std::map<std::string, glm::vec3> mymap)
{
  std::pair<std::string, glm::vec3> min
      = *std::min_element(mymap.begin(), mymap.end(), CompareSecond());
    //retrieve the data relevant to the closest planet.
    data = displacementsData[min.first];
  return min.second;
}
