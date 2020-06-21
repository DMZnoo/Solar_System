//
//  Debugger.cpp
//
//  Created by JINWOO LEE on 12/03/20.
//

#include "Debugger.hpp"
void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error =  glGetError())
    {
        std::cout << "[OpenGL Error] - " << error << ": " << function <<
        " " << file << ": " << line << std::endl;
        return false;
    };
    return true;
};

