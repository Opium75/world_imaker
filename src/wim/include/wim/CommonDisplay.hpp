//
// Created by piptouque on 23/12/2019.
//

#ifndef WORLD_IMAKER_COMMONDISPLAY_HPP
#define WORLD_IMAKER_COMMONDISPLAY_HPP

#pragma once


//Use glew as static library
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <glimac/glm.hpp>

//IMGUI
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <glimac/SDLWindowManager.hpp>

#include "Vec3D.hpp"

namespace wim
{


    typedef Point3Uint Anchor;

    typedef std::unique_ptr<glimac::SDLWindowManager> WindowManagerPtr;
    typedef glimac::SDLWindowManager::SDL_WindowPtr WindowPtr;



}

#endif //WORLD_IMAKER_COMMONDISPLAY_HPP
