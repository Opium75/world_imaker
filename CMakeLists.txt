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
set(GLU_DIRNAME glu-9.0.1)
set(GLUT_DIRNAME freeglut-3.2.1)
set(GLEW_DIRNAME glew-2.1.0)
set(SDL_DIRNAME SDL-1.2.15)
set(EIGEN3_DIRNAME eigen3)
set(GLM_DIRNAME glm)
set(GLIMAC_DIRNAME glimac)
set(IMGUI_DIRNAME imgui-master)

#

set(GLU_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${GLU_DIRNAME}/include)
set(GLUT_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${GLUT_DIRNAME})
set(GLUT_glut_LIBRARY ${PROJECT_EXTLIB_DIR}/{GLUT_DIRNAME}/lib)

set(GLEW_INCLUDE_DIRS ${PROJECT_EXTLIB_DIR}/${GLEW_DIRNAME}/include)

set(IMGUI_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${IMGUI_DIRNAME})

if(CYGWIN)
    set(GLEW_LIBRARIES ${PROJECT_EXTLIB_DIR}/${GLEW_DIRNAME}/bin)
    set(GLEW_LIB_FILEPATH ${GLEW_LIBRARIES}/Release/x64/glew32.dll)
endif(CYGWIN)

set(SDL_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${SDL_DIRNAME}/include)
set(SDL_LIBRARY ${PROJECT_EXTLIB_DIR}/${SDL_DIRNAME}/lib)
if(CYGWIN)
    set(SDL_LIB_FILEPATH ${SDL_LIBRARY}/libSDLmain.a)
endif(CYGWIN)

set(EIGEN3_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${EIGEN3_DIRNAME})
set(GLM_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${GLM_DIRNAME}/include)
set(GLIMAC_INCLUDE_DIR ${PROJECT_LIB_DIR}/${GLIMAC_DIRNAME}/include)
#

#OpenGL
message("Looking for OpenGL...")
find_package(OpenGL REQUIRED)
if(${OpenGL_FOUND})
    link_libraries(${OPENGL_LIBRARIES})
    message(STATUS "... found")
    message(STATUS "  version " ${OpenGL_VERSION_STRING})
    message(STATUS "  include " ${OpenGL_INCLUDE_DIR})

endif()


#SDL
#message("Looking for SDL...")
#find_package(SDL REQUIRED)
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

#GLUT
message("Looking for GLUT...")
find_package(GLUT REQUIRED)
if(${GLUT_FOUND})
    message(STATUS "...found")
    message(STATUS "  version " ${GLUT_VERSION_STRING})
    message(STATUS "  include " ${GLUT_INCLUDE_DIR})
endif()

#glew
if(NOT CYGWIN)
    message("Looking for glew...")
    find_package(GLEW REQUIRED)
    if(${GLEW_FOUND})
        link_libraries(${GLEW_LIBRARIES})
        message(STATUS "... found")
        message(STATUS "  version " ${GLEW_VERSION_STRING})
        message(STATUS "  include " ${GLEW_INCLUDE_DIRS})
    endif()
endif(NOT CYGWIN)


# lib include path
include_directories(${SDL_INCLUDE_DIR}
        \ ${OPENGL_INCLUDE_DIR}
        \ ${GLU_INCLUDE_DIR}
        \ ${GLUT_INCLUDE_DIR}
        \ ${GLEW_INCLUDE_DIRS}
        \ ${EIGEN3_INCLUDE_DIR}
        \ ${GLM_INCLUDE_DIR}
        \ ${GLIMAC_INCLUDE_DIR}
        \ ${IMGUI_INCLUDE_DIR}
        )


set(ALL_LIBRARIES
        \ ${SDL_LIBRARY}
        \ ${OPENGL_LIBRARIES}
        \ ${GLEW_LIBRARIES}
        \ ${SDL_LIBRARY}
        \ glimac
        \ glm)
add_subdirectory(${PROJECT_LIB_DIR}/${GLIMAC_DIRNAME}
        \ ${PROJECT_EXTLIB_DIR}/${GLM_DIRNAME}
      )

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
        src/wim/src/CubeStack.cpp
        src/wim/include/Vec3D.hpp
        src/wim/src/Vec3D.cpp
        src/wim/include/CubeWorld.hpp
        src/wim/src/CubeWorld.cpp
        src/wim/include/Randomiser.hpp
        src/wim/include/Randomisable.hpp
        src/wim/include/Displayer.hpp
        src/wim/src/Displayer.cpp
        src/wim/include/Exception.hpp
        src/wim/include/Window.hpp
        src/wim/include/wim.hpp
        ##IMGUI source files
        ${IMGUI_INCLUDE_DIR}/imgui.cpp
        ${IMGUI_INCLUDE_DIR}/imgui.h
        ${IMGUI_INCLUDE_DIR}/imgui_draw.cpp
        ${IMGUI_INCLUDE_DIR}/imgui_widgets.cpp
        )

if(CYGWIN)
    target_link_libraries(world_imaker
        ${CMAKE_SOURCE_DIR}/${SDL_LIB_FILEPATH}
        ${CMAKE_SOURCE_DIR}/${GLEW_LIB_FILEPATH}
        )
endif(CYGWIN)



