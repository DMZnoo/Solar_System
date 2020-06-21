//
//  Application.cpp
//
//  Created by JINWOO LEE on 27/04/20.
//

#include "Application.hpp"
GLFWwindow* window;
unsigned int width,height;
Application::Application()
{
    width = 1024;
    height = 768;
    
}
Application::Application(unsigned int windowWidth, unsigned int windowHeight) {
    width = windowWidth;
    height = windowHeight;
    
}

Application::~Application() { 
    glfwDestroyWindow(window);
        // Close OpenGL window and terminate GLFW
    glfwTerminate();
}


void Application::run() {
   // Initialise GLFW
     if( !glfwInit() )
     {
         fprintf( stderr, "Failed to initialize GLFW\n" );
         getchar();
         
     }
    
    //set sampling size
     glfwWindowHint(GLFW_SAMPLES, 4);
    //set version, has to equal to shader's version
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS compat.
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
     // Open a window and create its OpenGL context
     window = glfwCreateWindow( width, height, "Assignment 2", NULL, NULL);
     if( window == NULL ){
         fprintf( stderr, "Failed to open GLFW window.\n" );
         getchar();
         glfwTerminate();
         
     }
     glfwMakeContextCurrent(window);
 
     // Initialize GLEW
     glewExperimental = true; // Needed for core profile
     if (glewInit() != GLEW_OK) {
         fprintf(stderr, "Failed to initialize GLEW\n");
         getchar();
         glfwTerminate();
         
     }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    //capture cursor
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    //set initially to middle of the viewport
    glfwSetCursorPos(window,width/2,height/2);
    std::string planets[8] =
    {
        "earth",
        "mars",
        "mercury",
        "venus",
        "saturn",
        "uranus",
        "neptune",
        "jupiter"
        
    };
    //camera with free flow & object tracking
    Camera camera(width,height,&planets[0]);
    //<-----Renderers---->

    ModelRenderer sun("sun/sun.obj","sun");
    ModelRenderer mercury("mercury/mercury.obj","mercury");
    ModelRenderer venus("venus/venus.obj","venus");
    ModelRenderer earth("earth/earth.obj","earth");
    ModelRenderer moon("moon/moon.obj","moon");
    ModelRenderer mars("mars/mars.obj","mars");
    ModelRenderer jupiter("jupiter/jupiter.obj","jupiter");
    ModelRenderer saturn("saturn/saturn.obj","saturn");
    ModelRenderer uranus("uranus/uranus.obj","uranus");
    ModelRenderer neptune("neptune/neptune.obj","neptune");
    ModelRenderer asteroid("asteroid/asteroid.obj","asteroid");
    ModelRenderer path("path/path.obj","path");
    BatchRenderer asteroidBelt("grey.jpg","belt");
    ModelRenderer space("space/space.obj","space");
    

//    SkyboxRenderer skyRenderer;
    glEnable(GL_DEPTH_TEST);
     do{
         glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
         glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         camera.update();
         sun.render(camera);
         mercury.render(camera);
         venus.render(camera);
         earth.render(camera);
         moon.setLocation(earth.transferLocation());
         moon.render(camera);
         mars.render(camera);
         jupiter.render(camera);
         saturn.render(camera);
         uranus.render(camera);
         neptune.render(camera);
         asteroid.render(camera);
         path.render(camera);
         asteroidBelt.render(camera);
         
         //skybox
         space.render(camera);
//         skyRenderer.render(camera);
         // Swap buffers
         glfwSwapBuffers(window);
         glfwPollEvents();
 
     } // Check if the ESC key was pressed or the window was closed
     while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );
 
     // Close OpenGL window and terminate GLFW
     glfwTerminate();


       
}





