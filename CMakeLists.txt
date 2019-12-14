cmake_minimum_required(VERSION 3.10)

project(world_imaker)

# specify the system
# see: https://cmake.org/cmake/help/v2.9/manual/cmake-variables.7.html
message("CMAKE_VERSION          : " ${CMAKE_VERSION})
message("CMAKE_SYSTEM_NAME      : " ${CMAKE_SYSTEM_NAME})
message("CMAKE_SYSTEM           : " ${CMAKE_SYSTEM})
message("CMAKE_SYSTEM_PROCESSOR : " ${CMAKE_SYSTEM_PROCESSOR})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)

set(PROJECT_BINARY_DIR  build)
set(PROJECT_SOURCE_DIR  src)
set(PROJECT_LIB_DIR lib)
set(PROJECT_EXTLIB_DIR  third-party)


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
#file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output)
# put the binary files in this directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output)


## INCLUDE LIB ##
set(WIM_DIRNAME wim)

set(GLU_DIRNAME glu-9.0.1)
set(GLUT_DIRNAME freeglut-3.2.1)
set(GLEW_DIRNAME glew-2.1.0)
set(SDL_DIRNAME SDL-1.2.15)
set(EIGEN3_DIRNAME eigen3)
set(GLM_DIRNAME glm)
set(GLIMAC_DIRNAME glimac)
set(IMGUI_DIRNAME imgui-master)

#
set(WIM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/${WIM_DIRNAME}/include)
#

#OpenGL
message("Looking for OpenGL...")
find_package(OpenGL REQUIRED)
if(${OpenGL_FOUND})
    message(STATUS "... found")
    message(STATUS "  version " ${OpenGL_VERSION_STRING})
    message(STATUS "  include " ${OpenGL_INCLUDE_DIR})
endif()


#SDL
message("Looking for SDL...")
set(SDL_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${SDL_DIRNAME}/include)
set(SDL_LIBRARY_DIR ${PROJECT_EXTLIB_DIR}/${SDL_DIRNAME}/lib)
if(CYGWIN)
    set(SDL_LIBRARY ${CMAKE_HOME_DIRECTORY}/${SDL_LIBRARY_DIR}/win64/libSDLmain.a)
else()
    set(SDL_LIBRARY ${CMAKE_HOME_DIRECTORY}/${SDL_LIBRARY_DIR}/lin64/libSDL-1.2.so.0)
endif(CYGWIN)

#Eigen
message("Looking for Eigen...")
set(EIGEN3_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${EIGEN3_DIRNAME})
#find_package(Eigen3 REQUIRED)
#Nothing to do here ?
if(${EIGEN3_FOUND})
    message(STATUS "...found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
endif()

#GLUT
message("Looking for GLUT...")
set(GLUT_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${GLUT_DIRNAME}/include)
set(GLUT_LIBRARY_DIR ${PROJECT_EXTLIB_DIR}/${GLUT_DIRNAME}/lib)
if(CYGWIN)
    set(GLUT_glut_LIBRARY ${CMAKE_HOME_DIRECTORY}/${GLUT_LIBRARY_DIR}/...?)
else()
    set(GLUT_glut_LIBRARY ${CMAKE_HOME_DIRECTORY}/${GLUT_LIBRARY_DIR}/libglut.so)
endif(CYGWIN)

#find_package(GLUT REQUIRED)
if(${GLUT_FOUND})
    message(STATUS "...found")
    message(STATUS "  version " ${GLUT_VERSION_STRING})
    message(STATUS "  include " ${GLUT_INCLUDE_DIR})
endif()

#glew
set(GLEW_INCLUDE_DIRS ${PROJECT_EXTLIB_DIR}/${GLEW_DIRNAME}/include)
set(GLEW_LIBRARY_DIR ${PROJECT_EXTLIB_DIR}/${GLEW_DIRNAME}/lib)
if(CYGWIN)
    set(GLEW_LIBRARIES ${CMAKE_HOME_DIRECTORY}/${GLEW_LIBRARY_DIR}/win64/glew32.lib)
else()
    set(GLEW_LIBRARIES ${CMAKE_HOME_DIRECTORY}/${GLEW_LIBRARY_DIR}/lin64/libGLEW.so)
endif(CYGWIN)

#GLM
set(GLM_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${GLM_DIRNAME}/include)

# Include paths, inorder to use #include <....>
include_directories(${WIM_INCLUDE_DIR}
        \ ${SDL_INCLUDE_DIR}
        \ ${OPENGL_INCLUDE_DIR}
        \ ${GLUT_INCLUDE_DIR}
        \ ${GLEW_INCLUDE_DIRS}
        \ ${EIGEN3_INCLUDE_DIR}
        \ ${GLM_INCLUDE_DIR}
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
set(STATIC_LIBRARIES glimac imgui)

##### #####

set(ALL_LIBRARIES
        \ ${SDL_LIBRARY}
        \ ${OPENGL_LIBRARIES}
        \ ${GLEW_LIBRARIES}
        \ ${GLUT_glut_LIBRARY}
        \ ${STATIC_LIBRARIES}
        )

# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

add_executable(world_imaker
        ##WORLD IMAKER
        #source files
        main.cpp
        src/wim/src/Colour.cpp
        src/wim/src/Cube.cpp
        src/wim/src/CubeStack.cpp
        src/wim/src/Vec3D.cpp
        src/wim/src/CubeWorld.cpp
        src/wim/src/Displayer.cpp
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
        src/wim/include/wim/Window.hpp
        src/wim/include/wim/wim.hpp
        )

target_link_libraries(world_imaker
        ${STATIC_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${SDL_LIBRARY}
        ${GLEW_LIBRARIES}
        ${GLUT_glut_LIBRARY}
)

