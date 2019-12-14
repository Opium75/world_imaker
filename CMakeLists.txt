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
find_package(OpenGL REQUIRED)
message(STATUS "  version " ${OpenGL_VERSION_STRING})
message(STATUS "  include " ${OpenGL_INCLUDE_DIR})


#SDL2
message("Looking for SDL...")
set(SDL2_LIBRARY_DIR  ${PROJECT_EXTLIB_DIR}/${SDL2_DIRNAME}/lib)
set(SDL2_INCLUDE_DIR  ${PROJECT_EXTLIB_DIR}/${SDL2_DIRNAME}/include)
if(WIN32)
    #x86 or x64
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIBRARY "${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DIR}/x64/SDL2.lib;${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DIR}/x64/SDL2main.lib")
    else ()
        set(SDL2_LIBRARY "${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DIR}/x86/SDL2.lib;${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DIR}/x86/SDL2main.lib")
    endif ()
    string(STRIP "${SDL_LIBRARY}" SDL2_LIBRARIES)
else()
    find_package(SDL2 REQUIRED)
endif(WIN32)

message(STATUS " lib " ${SDL2_LIBRARY})
message(STATUS " include " ${SDL2_INCLUDE_DIR})

#Eigen
message("Looking for Eigen...")
set(EIGEN3_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${EIGEN3_DIRNAME})
find_package(Eigen3 REQUIRED)
#Nothing to do here ?
message(STATUS " include " ${EIGEN3_INCLUDE_DIR})

#GLUT
message("Looking for GLUT...")
set(GLUT_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${GLUT_DIRNAME}/include)
set(GLUT_LIBRARY_DIR ${PROJECT_EXTLIB_DIR}/${GLUT_DIRNAME}/lib)
if(WIN32)
    set(GLUT_glut_LIBRARY ${CMAKE_HOME_DIRECTORY}/${GLUT_LIBRARY_DIR}/x64/libgluts.lib)
else()
    set(GLUT_glut_LIBRARY ${CMAKE_HOME_DIRECTORY}/${GLUT_LIBRARY_DIR}/libglut.so.3.11.0)
endif(WIN32)
message(STATUS " include " ${GLUT_INCLUDE_DIR})
message(STATUS " lib " ${GLUT_glut_LIBRARY})

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
    set(GLEW_LIBRARIES ${CMAKE_HOME_DIRECTORY}/${GLEW_LIBRARY_DIR}/unix/libGLEW.so.2.1.0)
endif(WIN32)
message(STATUS " include " ${GLEW_INCLUDE_DIRS})
message(STATUS " lib " ${GLEW_LIBRARIES})



#GLM
set(GLM_INCLUDE_DIR ${PROJECT_EXTLIB_DIR}/${GLM_DIRNAME}/include)

# Include paths, in order to use #include <....>
include_directories(${WIM_INCLUDE_DIR}
        ${SDL2_INCLUDE_DIR}
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
        ${SDL2_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLUT_glut_LIBRARY}
        ${INTERN_LIBRARIES}
        )

# compilation flags
if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 ")
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "/g")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
endif(WIN32)

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
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLUT_glut_LIBRARY}
        ${INTERN_LIBRARIES}
        ${SDL2_LIBRARY}
        )

if(WIN32)
    ###ADDING SDL2 DLLs to ouput folder###
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIBRARY_DLL ${SDL2_LIBRARY_DIR}/x64/SDL2.dll)
    else()
        set(SDL2_LIBRARY_DLL ${SDL2_LIBRARY_DIR}/x86/SDL2.dll)
    endif()
    message(STATUS ${SDL2_LIBRARY_DLL})
    add_custom_command(TARGET world_imaker POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${CMAKE_HOME_DIRECTORY}/${SDL2_LIBRARY_DLL}"
                    $<TARGET_FILE_DIR:world_imaker>)
endif(WIN32)