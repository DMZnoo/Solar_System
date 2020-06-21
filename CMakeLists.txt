# CMake entry point

cmake_minimum_required (VERSION 3.0)
project (Portfolio_Jinwoo_Lee)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (lib)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/cmake-modules")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP





include_directories(
	lib/glfw-3.3.2/include/
	lib/glm/
	lib/glew-2.1.0/include/
	lib/assimp-3.0.1270/include/
	.
	
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_210
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Assignment 2
file(GLOB_RECURSE SRC
	"Source/*.hpp"
	"Source/*.cpp"
	"Source/GLSL/*.glsl"
	"Source/Resources/*.jpg"

)
add_executable(Portfolio_Jinwoo_Lee ${SRC})



target_link_libraries(Portfolio_Jinwoo_Lee
	${ALL_LIBS}
	assimp
)

set_target_properties(Portfolio_Jinwoo_Lee PROPERTIES COMPILE_DEFINITIONS "USE_ASSIMP")
# Xcode and Visual working directories
set_target_properties(Portfolio_Jinwoo_Lee PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source/")
create_target_launcher(Portfolio_Jinwoo_Lee WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Source/")



SOURCE_GROUP(Shader REGULAR_EXPRESSION ".*/Shader/.*" )
SOURCE_GROUP(GLSL REGULAR_EXPRESSION ".*/GLSL/.*" )
SOURCE_GROUP(Control REGULAR_EXPRESSION ".*/Control/.*" )
SOURCE_GROUP(Utility REGULAR_EXPRESSION ".*/Utility/.*" )
SOURCE_GROUP(Renderer REGULAR_EXPRESSION ".*/Renderer/.*" )
SOURCE_GROUP(Model REGULAR_EXPRESSION ".*/Model/.*" )
SOURCE_GROUP(Resources REGULAR_EXPRESSION ".*/Resources/.*" )
SOURCE_GROUP(Texture REGULAR_EXPRESSION ".*/Texture/.*" )
SOURCE_GROUP(Entity REGULAR_EXPRESSION ".*/Entity/.*" )

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET Portfolio_Jinwoo_Lee POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Portfolio_Jinwoo_Lee${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Source/"
)


elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )