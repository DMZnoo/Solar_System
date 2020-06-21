//
//  CubeTexture.hpp
//
//  Created by JINWOO LEE on 30/04/20.
//

#ifndef BaseTexture_hpp
#define BaseTexture_hpp
#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>
#include "../Utility/stb_image.h"
#include "../Debugger.hpp"
#include "../Utility/NonCopyable.hpp"

class BaseTexture : public NonCopyable
{
    public:
        BaseTexture() = default;
        unsigned int LoadTexture(char const*path);
        void Bind2DTexture();
        ~BaseTexture();
    private:
        unsigned int textID;
        int width,height,number_of_components;
};

#endif /* BaseTexture_hpp */
