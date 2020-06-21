//
//  Player.hpp
//  Entity.hpp

//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 12/05/20.
//

#ifndef Entity_hpp
#define Entity_hpp
#include <glm/glm.hpp>
#include <string>
#include "../Utility/NonCopyable.hpp"
struct Entity : public NonCopyable
{
	glm::vec3 Rotation;
	glm::vec3 Direction;
	glm::vec3 Position;
	void clear()
	{
		Rotation = glm::vec3(0.f);
		Direction = glm::vec3(0.f);
		Position = glm::vec3(0.f);
	}
};
#endif /* Entity_hpp */

