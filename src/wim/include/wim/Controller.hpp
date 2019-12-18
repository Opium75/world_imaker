//
// Created by yoann on 17/12/2019.
//

#ifndef WORLD_IMAKER_CONTROLLER_HPP
#define WORLD_IMAKER_CONTROLLER_HPP

#pragma once

#include <SDL2/SDL.h>

#include "Displayer.hpp"

namespace wim
{
    class DisplayController {
    private:
        Displayer _disp;
    public:
        DisplayController(const char* appPath): _disp(appPath) {}
        void runDisplay() const;

        inline const glimac::SDLWindowManager::SDL_WindowPtr& getWindowPtr()const {return _disp.getWindowPtr();}
        inline const SDL_GLContext& getGLContext()const {return _disp.getGLContext();}

    };

    class UIController
    {
    private:
    public:
        bool runInterface() const;
    };

    class ComputeController
    {
    private:
    public:
        void runCompute() const
        {
            /* Compute calculations on Model
             * add cubes, etc..
             * depending on what was decided
             * by UICOntroller
             */
        }
    };

    class Controller {
    private:
        DisplayController _dispCtrl;
        UIController _uiCtrl;
        ComputeController _compCtrl;
    public:
        Controller(const char* appPath): _dispCtrl(appPath), _uiCtrl() {}

        bool runLoop() const;

        void runApp() const
        {
            while( this->runLoop() );
        }


    };


}
#endif //WORLD_IMAKER_CONTROLLER_HPP
