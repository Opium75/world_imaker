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
        DisplayController(): _disp()
        {}
        void runDisplay()
        {
            _disp.displayAll();

        }
    };

    class UIController
    {
    private:
    public:
        bool runInterface()
        {

            bool loop = true;

            SDL_Event e;
            while(SDL_PollEvent(&e))
            {
                //ImGui does its thing
                ImGui_ImplSDL2_ProcessEvent(&e);

                switch(e.type)
                {
                    case SDL_QUIT :
                        loop = false;
                        break;

                        

                    default :
                        break;
                }
            }

            return loop;

        }
    };

    class ComputeController
    {
    private:
    public:
        void runCompute()
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
        Controller(): _dispCtrl(), _uiCtrl()
        {}

        bool runLoop()
        {
            bool loop;
            /* */
            //display
            _dispCtrl.runDisplay();
            //user interface (managing input)
            loop = _uiCtrl.runInterface();
            //calculating results
            _compCtrl.runCompute();

            return loop;
        }

        void runApp()
        {
            while( this->runLoop() );
        }


    };


}
#endif //WORLD_IMAKER_CONTROLLER_HPP
