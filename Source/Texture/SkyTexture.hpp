//
//  SkyTexture.hpp
//
//  Created by JINWOO LEE on 2/05/20.
//

#ifndef SkyTexture_hpp
#define SkyTexture_hpp

#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>
#include "../Utility/stb_image.h"
#include "../Debugger.hpp"
#include "../Utility/NonCopyable.hpp"

class SkyTexture : public NonCopyable
{
    public:
        SkyTexture() = default;
        void LoadCubeMap(std::vector<std::string> sides);
        void BindCubeMapTexture();
        ~SkyTexture();
    private:
        unsigned int textID;
        int width,height,number_of_components;
};
#endif /* SkyTexture_hpp */
