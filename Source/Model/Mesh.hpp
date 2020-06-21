//
//  Mesh.hpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 30/04/20.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int textID;
    std::string type;
    std::string name;
};
struct Mesh
{
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    void reset()
    {
        std::vector<Vertex>().swap(vertices);
        std::vector<unsigned int>().swap(indices);
        std::vector<Texture>().swap(textures);
    }
    
};

#endif /* Mesh_hpp */
