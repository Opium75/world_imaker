cmake_minimum_required(VERSION 3.7)

project(world_imaker)

# specify the system
# see: https://cmake.org/cmake/help/v2.9/manual/cmake-variables.7.html
message("CMAKE_VERSION          : " ${CMAKE_VERSION})
message("CMAKE_SYSTEM_NAME      : " ${CMAKE_SYSTEM_NAME})
message("CMAKE_SYSTEM           : " ${CMAKE_SYSTEM})
message("CMAKE_SYSTEM_PROCESSOR : " ${CMAKE_SYSTEM_PROCESSOR})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)

set(PROJECT_BINARY_DIR  bin)
set(PROJECT_SOURCE_DIR  src)
set(PROJECT_LIB_DIR lib)
set(PROJECT_EXTLIB_DIR  third-party)

set(PROJECT_EXEC_NAME world_imaker)
set(PROJECT_RESOURCE_DIR resources)
set(PROJECT_SHADER_DIR shaders)
set(PROJECT_TEXTURE_DIR textures)

# specify the directories
message("CMAKE_BINARY_DIR       : " ${CMAKE_BINARY_DIR})
message("CMAKE_SOURCE_DIR       : " ${CMAKE_SOURCE_DIR})
message("CMAKE_HOME_DIRECTORY   : " ${CMAKE_HOME_DIRECTORY})
message("PROJECT_BINARY_DIR     : " ${PROJECT_BINARY_DIR})
message("PROJECT_SOURCE_DIR     : " ${PROJECT_SOURCE_DIR})
message("PROJECT_LIB_DIR     : " ${PROJECT_LIB_DIR})
message("PROJECT_EXTLIB_DIR     : " ${PROJECT_EXTLIB_DIR})


set(CMAKE_CXX_STANDARD 17)

# add a "output" directory in the project binary directory
# put the binary files in this directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/wim)


## INCLUDE LIB ##
set(WIM_DIRNAME wim)

set(GLUT_DIRNAME freeglut-3.2.1)
set(GLEW_DIRNAME glew-2.1.0)
set(SDL2_DIRNAME SDL2-2.0.10)
set(EIGEN3_DIRNAME eigen3)
set(GLM_DIRNAME glm)
set(GLIMAC_DIRNAME glimac)
set(IMGUI_DIRNAME imgui-master)

#
set(WIM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/${WIM_DIRNAME}/include)
#

#OpenGL
message("Looking for OpenGL...")
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
message(STATUS "  version " ${OpenGL_VERSION_STRING})
message(STATUS "  include " ${OpenGL_INCLUDE_DIR})


#SDL2
message("Looking for SDL...")
if(WIN32)
    set(SDL2_LIBRARY_DIR  ${PROJECT_EXTLIB_DIR}/${SDL2_DIRNAME}/lib)
    set(SDL2_INCLUDE_DIRS  ${PROJECT_EXTLIB_DIR}/${SDL2_DIRNAME}/include)
    #x86 or x64
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIBRARY "${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DIR}/x64/SDL2.lib;${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DIR}/x64/SDL2main.lib")
    else ()
        set(SDL2_LIBRARY "${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DIR}/x86/SDL2.lib;${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DIR}/x86/SDL2main.lib")
    endif ()
    string(STRIP "${SDL2_LIBRARY}" SDL2_LIBRARIES)
else()
    find_package(SDL2 REQUIRED)
endif(WIN32)
message(STATUS " include " ${SDL2_INCLUDE_DIR})
message(STATUS " lib " ${SDL2_LIBRARIES})

#Eigen
message("Looking for Eigen...")
set(EIGEN3_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${EIGEN3_DIRNAME})
find_package(Eigen3 REQUIRED)
#Nothing to do here ?
message(STATUS " include " ${EIGEN3_INCLUDE_DIR})

#glew
message("Looking for GLEW...")
set(GLEW_INCLUDE_DIRS ${PROJECT_EXTLIB_DIR}/${GLEW_DIRNAME}/include)
set(GLEW_LIBRARY_DIR ${PROJECT_EXTLIB_DIR}/${GLEW_DIRNAME}/lib)
if(WIN32)
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(GLEW_LIBRARIES "${CMAKE_HOME_DIRECTORY}/${GLEW_LIBRARY_DIR}/x64/glew32s.lib")
    else()
        set(GLEW_LIBRARIES "${CMAKE_HOME_DIRECTORY}/${GLEW_LIBRARY_DIR}/x86/glew32s.lib")
    endif()
else()
    set(GLEW_LIBRARIES ${CMAKE_HOME_DIRECTORY}/${GLEW_LIBRARY_DIR}/unix/libGLEW.a)
endif(WIN32)
message(STATUS " include " ${GLEW_INCLUDE_DIRS})
message(STATUS " lib " ${GLEW_LIBRARIES})


#GLUT
message("Looking for GLUT...")
set(GLUT_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${GLUT_DIRNAME}/include)
set(GLUT_LIBRARY_DIR ${PROJECT_EXTLIB_DIR}/${GLUT_DIRNAME}/lib)
if(WIN32)
    set(GLUT_glut_LIBRARY ${CMAKE_HOME_DIRECTORY}/${GLUT_LIBRARY_DIR}/x64/freeglutd.lib)
else()
    set(GLUT_glut_LIBRARY ${CMAKE_HOME_DIRECTORY}/${GLUT_LIBRARY_DIR}/unix/libglut.so)
endif(WIN32)
message(STATUS " include " ${GLUT_INCLUDE_DIR})
message(STATUS " lib " ${GLUT_glut_LIBRARY})

#GLM
set(GLM_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${GLM_DIRNAME}/include)

# Include paths, in order to use #include <....>
include_directories(${WIM_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
        )

### INTERNAL STATIC LIBS ###

#imgui
set(IMGUI_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${IMGUI_DIRNAME})
add_subdirectory(${IMGUI_INCLUDE_DIR})

#glimac
set(GLIMAC_INCLUDE_DIR ${PROJECT_LIB_DIR}/${GLIMAC_DIRNAME}/include)
add_subdirectory(${PROJECT_LIB_DIR}/${GLIMAC_DIRNAME})
##

include_directories(
        ${IMGUI_INCLUDE_DIR}
      \ ${GLIMAC_INCLUDE_DIR}
)
set(INTERN_LIBRARIES glimac imgui)

##### #####


set(ALL_LIBRARIES
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLUT_glut_LIBRARY}
        ${INTERN_LIBRARIES}
        ${SDL2_LIBRARIES}
        )

# compilation flags
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 ")
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "/g")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -std=c++${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
endif(WIN32)

add_executable(${PROJECT_EXEC_NAME}
        ##WORLD IMAKER
        #source files
        main.cpp
        src/wim/src/Colour.cpp
        src/wim/src/Cube.cpp
        src/wim/src/CubeStack.cpp
        src/wim/src/CubeWorld.cpp
        src/wim/src/Displayer.cpp
        src/wim/src/Controller.cpp
        src/wim/src/ShaderManager.cpp
        src/wim/src/ShaderSender.cpp
        src/wim/src/CameraManager.cpp
        src/wim/src/SceneRenderer.cpp
        src/wim/src/BufferManager.cpp
        src/wim/src/Light.cpp
        src/wim/src/PatternManager.cpp
        src/wim/src/Interface.cpp
        src/wim/src/Listener.cpp
        src/wim/src/TextureManager.cpp
        src/wim/src/Displayable.cpp
        src/wim/src/Cursor.cpp
        src/wim/src/FBO.cpp
        src/wim/src/ITO.cpp
        src/wim/src/SSBO.cpp
        src/wim/src/Uniform.cpp
        #headers
        src/wim/include/wim/Displayer.hpp
        src/wim/include/wim/Vec3D.hpp
        src/wim/include/wim/CubeWorld.hpp
        src/wim/include/wim/CubeStack.hpp
        src/wim/include/wim/Randomiser.hpp
        src/wim/include/wim/Randomisable.hpp
        src/wim/include/wim/Displayable.hpp
        src/wim/include/wim/Cube.hpp
        src/wim/include/wim/Colour.hpp
        src/wim/include/wim/Exception.hpp
        src/wim/include/wim/WidgetManager.hpp
        src/wim/include/wim/wim.hpp
        src/wim/include/wim/Controller.hpp
        src/wim/include/wim/ShaderSender.hpp
        src/wim/include/wim/ShaderManager.hpp
        src/wim/include/wim/Light.hpp
        src/wim/include/wim/CameraManager.hpp
        src/wim/include/wim/PatternManager.hpp
        src/wim/include/wim/SceneRenderer.hpp
        src/wim/include/wim/Types.hpp
        src/wim/include/wim/Model.hpp
        src/wim/include/wim/Material.hpp
        src/wim/include/wim/CommonDisplay.hpp
        src/wim/include/wim/BufferManager.hpp
        src/wim/include/wim/Interface.hpp
        src/wim/include/wim/Listener.hpp
        src/wim/include/wim/CommonPath.hpp
        src/wim/include/wim/Cursor.hpp
        src/wim/include/wim/Selectable.hpp
        src/wim/include/wim/BufferObject.hpp
        src/wim/include/wim/FBO.hpp
        src/wim/include/wim/ITO.hpp
        src/wim/include/wim/SSBO.hpp
        src/wim/include/wim/Uniform.hpp
        src/wim/include/wim/BufferData.hpp
        )
target_link_libraries(${PROJECT_EXEC_NAME}
        ${ALL_LIBRARIES}
        )

if(WIN32)
    message("Adding DLL to executable dir:")
    ###ADDING SDL2 DLL to output folder for runtime library###
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIBRARY_DLL ${SDL2_LIBRARY_DIR}/x64/SDL2.dll)
    else()
        set(SDL2_LIBRARY_DLL ${SDL2_LIBRARY_DIR}/x86/SDL2.dll)
    endif()
    message(STATUS "Copying DLL: ${SDL2_LIBRARY_DLL}")
    add_custom_command(TARGET ${PROJECT_EXEC_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DLL}"
                    $<TARGET_FILE_DIR:${PROJECT_EXEC_NAME}>)
endif(WIN32)

##SHADERS##
#adding Shaders to build directory after compiling
message("Adding Shaders and config to executable dir:")
file(GLOB SHADERS ${PROJECT_RESOURCE_DIR}/${PROJECT_SHADER_DIR}/*.glsl ${PROJECT_RESOURCE_DIR}/${PROJECT_SHADER_DIR}/*.conf)
foreach(SHADER ${SHADERS})
    file( RELATIVE_PATH SHADER_REL ${CMAKE_HOME_DIRECTORY}/${PROJECT_RESOURCE_DIR}/${PROJECT_SHADER_DIR} ${SHADER})
    message(STATUS "Copying shader: ${SHADER_REL} to ${CMAKE_BINARY_DIR}/${PROJECT_BINARY_DIR}/${PROJECT_RESOURCE_DIR}/${PROJECT_SHADER_DIR}/${SHADER_REL}")
    configure_file(${SHADER} ${CMAKE_BINARY_DIR}/${PROJECT_BINARY_DIR}/${PROJECT_RESOURCE_DIR}//${PROJECT_SHADER_DIR}/${SHADER_REL} COPYONLY)
endforeach()

##Textures##
#adding Shaders to build directory after compiling
message("Adding textures and config to executable dir:")
file(GLOB TEXTURES ${PROJECT_RESOURCE_DIR}/${PROJECT_TEXTURE_DIR}/*.png ${PROJECT_RESOURCE_DIR}/${PROJECT_TEXTURE_DIR}/*.conf)
foreach(TEXTURE ${TEXTURES})
    file( RELATIVE_PATH TEXTURE_REL ${CMAKE_HOME_DIRECTORY}/${PROJECT_RESOURCE_DIR}/${PROJECT_TEXTURE_DIR} ${TEXTURE})
    message(STATUS "Copying texture: ${TEXTURE_REL} to ${CMAKE_BINARY_DIR}/${PROJECT_BINARY_DIR}/${PROJECT_RESOURCE_DIR}/${PROJECT_TEXTURE_DIR}/${TEXTURE_REL}")
    configure_file(${TEXTURE} ${CMAKE_BINARY_DIR}/${PROJECT_BINARY_DIR}/${PROJECT_RESOURCE_DIR}//${PROJECT_TEXTURE_DIR}/${TEXTURE_REL} COPYONLY)
endforeach()