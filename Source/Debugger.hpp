//
//  Debugger.hpp
//
//  Created by JINWOO LEE on 12/03/20.
//

#ifndef Debugger_hpp
#define Debugger_hpp
#include <iostream>
#include <GL/glew.h>

//compiler specific assert function to break when an error happens
#if defined( _MSC_VER )
    #define ASSERT(x) if(!(x)) __debugbreak();
    #pragma warning(disable:4127) /* Conditional expression is constant (the do-while) */
#elif defined( __GNUC__ )
    #define ASSERT(x) if(!(x)) __builtin_trap();
#else
    #error Unsupported compiler
#endif

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();

bool GLLogCall(const char * function, const char * file, int line);




#endif /* Debugger_hpp */
