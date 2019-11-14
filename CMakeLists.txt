cmake_minimum_required(VERSION 3.15)

# specify the system
# see: https://cmake.org/cmake/help/v2.9/manual/cmake-variables.7.html
message("CMAKE_VERSION          : " ${CMAKE_VERSION})
message("CMAKE_SYSTEM_NAME      : " ${CMAKE_SYSTEM_NAME})
message("CMAKE_SYSTEM           : " ${CMAKE_SYSTEM})
message("CMAKE_SYSTEM_PROCESSOR : " ${CMAKE_SYSTEM_PROCESSOR})

# specify the directories
message("CMAKE_BINARY_DIR       : " ${CMAKE_BINARY_DIR})
message("CMAKE_SOURCE_DIR       : " ${CMAKE_SOURCE_DIR})
message("CMAKE_HOME_DIRECTORY   : " ${CMAKE_HOME_DIRECTORY})
message("PROJECT_BINARY_DIR     : " ${PROJECT_BINARY_DIR})
message("PROJECT_SOURCE_DIR     : " ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

# add a "output" directory in the project binary directory
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output)

# put the binary files in this directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

## INCLUDE LIB ##
#OpenCV
message("Looking for OpenCV...")
find_package(OpenCV REQUIRED)
if(${OpenCV_FOUND})
    message(STATUS "... found")
    message(STATUS "  version     : " ${OpenCV_VERSION})
    message(STATUS "  include dir : " ${OpenCV_INCLUDE_DIRS})
    message(STATUS "  libraries   : ")
    foreach(opencvLibs ${OpenCV_LIBS})
        message("        " ${opencvLibs})
    endforeach()
endif()
# check opencv version
if(${OpenCV_VERSION} VERSION_LESS 2.0.0)
    message(FATAL_ERROR “OpenCV version is not compatible : ${OpenCV_VERSION}”)
endif()
# lib include path
include_directories(${OpenCV_INCLUDE_DIRS})

#Eigen
message("Looking for Eigen...")
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "...found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
endif()
# lib include path
include_directories(${EIGEN3_INCLUDE_DIR})


project(world_imaker)

# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")



add_executable(world_imaker main.cpp)