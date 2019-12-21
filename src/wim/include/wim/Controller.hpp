//
// Created by yoann on 17/12/2019.
//

#ifndef WORLD_IMAKER_CONTROLLER_HPP
#define WORLD_IMAKER_CONTROLLER_HPP

#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include "Displayer.hpp"
#include "Model.hpp"

namespace wim
{
    class AbstractController
    {
    protected:
        typedef std::unique_ptr<Displayer> DisplayerPtr;
        typedef std::unique_ptr<Model> ModelPtr;
    protected:
        static DisplayerPtr _displayer;
        static ModelPtr _model;
    protected:
        inline const DisplayerPtr& getDisplayer() const {return _displayer;}
        inline DisplayerPtr& getDisplayer() {return _displayer;}

        inline const ModelPtr& getModel() const { return _model;}
        inline ModelPtr& getModel() {return _model;}
    };


    class DisplayController : protected AbstractController
            {
    private:
    public:
        DisplayController(const char* appPath, const LightManagerPtr& lights)
        {
            //initialising display
            _displayer.reset(new Displayer(appPath, lights));
        }
        void runDisplay() const;

        inline const glimac::SDLWindowManager::SDL_WindowPtr& getWindowPtr()const {return _displayer->getWindowPtr();}
        inline const SDL_GLContext& getGLContext()const {return _displayer->getGLContext();}

    };

    class UIController : protected AbstractController
    {
    private:
    public:
        bool runInterface() const;
    };

    class ComputeController : protected AbstractController
    {
    private:
    public:
        ComputeController() = default;
        ComputeController(const XUint worldWidth, const YUint worldLength)
        {
            //initialsation world
            _model.reset(new Model(worldWidth, worldLength));
        }
        void runCompute() const
        {
            /* Compute calculations on Model
             * add cubes, etc..
             * depending on what was decided
             * by UICOntroller
             */
        }
    };

    class MasterController : protected AbstractController
    {
    private:
        /* ComputeController needs to be initialiased first
        * before it initialises the model too
         * And the display uses a shared pointer to lights.
         */
        ComputeController _compCtrl;
        DisplayController _dispCtrl;
        UIController _uiCtrl;
    public:
        MasterController(const char* appPath, const XUint worldWidth, const YUint worldLength):
                _compCtrl(worldWidth, worldLength),_dispCtrl(appPath, _model->getLightManagerPtr()), _uiCtrl()  {}

        bool runLoop() const;

        void runApp() const
        {
            while( this->runLoop() );
        }


    };



}
#endif //WORLD_IMAKER_CONTROLLER_HPP
