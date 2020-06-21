//
//  Main.cpp
//
//  Created by JINWOO LEE on 3/03/20.
//



#include "Application.hpp"

//Replace with your root to the source folder
std::string ROOT = "/Users/daniel/Downloads/opengl_portfolio/Source/Resources/";
const float PI = acos(-1);
bool LOCK_ON_OBJECT = false;



int main( void )
{
    Application app(1024,768);
    app.run();
    return 0;
}

