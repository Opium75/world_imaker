//
// Created by piptouque on 28/12/2019.
//

#ifndef WORLD_IMAKER_COMMUNPATH_HPP
#define WORLD_IMAKER_COMMUNPATH_HPP

#pragma  once

#include <string>
#include <iostream>
#include <fstream>
#include <glimac/FilePath.hpp>

#include "Types.hpp"
#include "Exception.hpp"

namespace wim
{

    /* Path to shaders and config file relative to build directory */
    static constexpr const char* DEFAULT_RESOURCES_DIR = "resources";
    static constexpr const char* DEFAULT_SHADER_DIR = "shaders";
    static constexpr const char* DEFAULT_SHADER_CONF_FILENAME = "shaders.conf";

    static constexpr const char* DEFAULT_TEXTURE_DIR = "textures";
    static constexpr const char* DEFAULT_TEXTURE_CONF_FILENAME = "textures.conf";

    /* Constant used in shader files loading?*/
    static const unsigned int MAX_SIZE_FILENAME = 30;
    static const char SEP = glimac::FilePath::PATH_SEPARATOR; //defined in FilePat
}
#endif //WORLD_IMAKER_COMMUNPATH_HPP
