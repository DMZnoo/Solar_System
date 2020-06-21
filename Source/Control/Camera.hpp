//
//  Camera.hpp
//
//  Created by JINWOO LEE on 27/04/20.
//

#ifndef Camera_hpp
#define Camera_hpp


#include <GLFW/glfw3.h>
#include "../Entity/Entity.hpp" 
#include "Controller.hpp"
#include <map>
#include <algorithm>
extern unsigned int width,height;
typedef std::pair<std::string, glm::vec3> MyPairType;
struct CompareSecond
{
    bool operator()(const MyPairType& left, const MyPairType& right) const
    {
        float leftVal = sqrt(pow(left.second.x,2)+pow(left.second.y,2)+pow(left.second.z,2));
        float rightVal = sqrt(pow(right.second.x,2)+pow(right.second.y,2)+pow(right.second.z,2));
        return leftVal < rightVal;
    }
};

class Camera : public Entity
{
public:
    Camera(int width, int height, std::string *array);
    void update();
    void init();
    const glm::mat4 &getViewMatrix();
    const glm::mat4 &getProjMatrix();
    void setViewMatrix(glm::mat4 viewMatrix);
    void cameraPosUpdate(glm::vec3 objPos);
    void cameraDirUpdate(glm::vec3 dir);
    glm::vec3 getCamPos();
    void addDisplacement(std::string type,glm::vec3 disp,float radius, float angle);
    glm::vec3 returnSmallest();
    glm::vec3 getMin(std::map<std::string, glm::vec3> mymap);
    glm::vec2 getData();
private:
    Controller controller;
    glm::mat4 i_viewMatrix;
    glm::mat4 i_projMatrix;
    float RotatedAngle,x,y,z,radius;
    glm::vec3 objDistance;
    glm::vec2 data;
    std::map<std::string,glm::vec3> displacements;
    std::map<std::string,glm::vec2> displacementsData;
    
    

    
    
};

#endif /* Camera_hpp */
