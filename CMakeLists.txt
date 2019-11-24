cmake_minimum_required(VERSION 3.10)

# specify the system
# see: https://cmake.org/cmake/help/v2.9/manual/cmake-variables.7.html
message("CMAKE_VERSION          : " ${CMAKE_VERSION})
message("CMAKE_SYSTEM_NAME      : " ${CMAKE_SYSTEM_NAME})
message("CMAKE_SYSTEM           : " ${CMAKE_SYSTEM})
message("CMAKE_SYSTEM_PROCESSOR : " ${CMAKE_SYSTEM_PROCESSOR})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

set(PROJECT_BINARY_DIR ./build)
set(PROJECT_SOURCE_DIR  ./src)
set(PROJECT_LIB_DIR ./lib)
set(PROJECT_EXTLIB_DIR ./third-party)

# specify the directories
message("CMAKE_BINARY_DIR       : " ${CMAKE_BINARY_DIR})
message("CMAKE_SOURCE_DIR       : " ${CMAKE_SOURCE_DIR})
message("CMAKE_HOME_DIRECTORY   : " ${CMAKE_HOME_DIRECTORY})
message("PROJECT_BINARY_DIR     : " ${PROJECT_BINARY_DIR})
message("PROJECT_SOURCE_DIR     : " ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)


# add a "output" directory in the project binary directory
#file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output)
# put the binary files in this directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

## INCLUDE LIB ##


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
find_package(SDL REQUIRED)
if(${SDL_FOUND})
    message(STATUS "... found")
    message(STATUS "  version " ${SDL_VERSION_STRING})
    message(STATUS "  include " ${SDL_INCLUDE_DIR})
endif()

#Eigen
message("Looking for Eigen...")
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "...found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
endif()

set(GLM_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/glm/include)
set(GLIMAC_INCLUDE_DIR ${PROJECT_LIB_DIR}/glimac/include)

# lib include path
include_directories(${SDL_INCLUDE_DIR}
        \ ${OPENGL_INCLUDE_DIR}
        \ ${GLEW_INCLUDE_DIR}
        \ ${EIGEN3_INCLUDE_DIR}
        \ ${GLM_INCLUDE_DIR}
        \ ${GLIMAC_INCLUDE_DIR})

set(ALL_LIBRARIES
        \ ${SDL_LIBRARY}
        \ ${OPENGL_LIBRARIES}
        \ ${GLEW_LIBRARY}
        \ glimac
        \ glm)

add_subdirectory(${PROJECT_LIB_DIR}/glimac
        \ ${PROJECT_EXTLIB_DIR}/glm)

# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")


add_executable(world_imaker main.cpp
        src/wim/include/Cube.hpp
        src/wim/include/Colour.hpp
        src/wim/src/Colour.cpp
        src/wim/include/Displayable.hpp
        src/wim/src/Cube.cpp
        src/wim/include/CubeStack.hpp
        src/wim/src/CubeStack.cpp src/wim/include/Vec3D.hpp src/wim/src/Vec3D.cpp src/wim/include/CubeWorld.hpp src/wim/src/CubeWorld.cpp src/wim/include/Randomiser.hpp src/wim/include/Randomisable.hpp)


