//
// Created by piptouque on 25/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYER_HPP
#define WORLD_IMAKER_DISPLAYER_HPP
#pragma  once

//Use glew as static library
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

#include <glimac/SDLWindowManager.hpp>

#include "Exception.hpp"
#include "Widgets.hpp"
//#include "ShaderManager.hpp"

#include "Cube.hpp"
#include "CubeStack.hpp"
#include "CubeWorld.hpp"


namespace wim {
    //default values for the SDL display window.
    static const float DISP_WINDOW_WIDTH = 600.f;
    static const float DISP_WINDOW_HEIGHT = 400.f;
    constexpr static const char* DISP_WINDOW_NAME = "wim"; //Look! We used constexpr!
    //Visitor class
    class Displayer {
    private:
        typedef std::unique_ptr<glimac::SDLWindowManager> WManagerPtr;
        WManagerPtr _manager;
        //ShaderManager _shaders;
        Widgets _widget;
    public:
        Displayer(const char* appPath) : _manager(),_widget()
        {
            this->initDisplay(appPath);
            //std::cout << _shaders;
        }
        ~Displayer() = default;

        //const methods until I know what to do with them
        void display(const Cube &cube) const;
        void display(const CubeStack &stack) const;
        void display(const CubeWorld &world) const;
        void display(const Widgets &widget) const;

        void displayAll() const;

        inline const glimac::SDLWindowManager::SDL_WindowPtr& getWindowPtr() const {return _manager->getWindowPtr();};
        inline const SDL_GLContext& getGLContext() const {return _manager->getGlContext();};

    private:
        //todo: WE'VE GOT TO HOLD ON TO WHAT WE'VE GOT
        //todo: IT DOESN'T EVEN MATTER IF WE MAKE IT OR NOT
       void initDisplay(const char* appPath);
    };
}

#endif //WORLD_IMAKER_DISPLAYER_HPP
