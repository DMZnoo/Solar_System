//
//  CubeTexture.cpp
//
//  Created by JINWOO LEE on 30/04/20.
//

#include "BaseTexture.hpp"

unsigned int BaseTexture::LoadTexture(char const * path) {
    GLCall(glGenTextures(1,&textID));
    unsigned char *data = stbi_load(path, &width, &height, &number_of_components, 0);
    if(data)
        {
            glEnable(GL_TEXTURE_2D);
            GLCall(glBindTexture(GL_TEXTURE_2D, textID));
            GLCall(glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data));
            GLCall(glGenerateMipmap(GL_TEXTURE_2D));
            
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); //use linear filter
            stbi_set_flip_vertically_on_load(false);
            stbi_image_free(data);
        }
    else
        {
            std::cout << "Texture failed at load, Path: "  << path << std::endl;
            stbi_image_free(data);
        }
    return textID;
}


void BaseTexture::Bind2DTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textID);
};

BaseTexture::~BaseTexture() { 
    
}
