//
// Created by yoann on 17/12/2019.
//

#ifndef WORLD_IMAKER_CONTROLLER_HPP
#define WORLD_IMAKER_CONTROLLER_HPP

#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include "Exception.hpp"
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
        static ModelPtr _model;
        static DisplayerPtr _displayer;
    protected:
        inline const DisplayerPtr& getDisplayer() const {return _displayer;}
        inline DisplayerPtr& getDisplayer() {return _displayer;}

        inline const ModelPtr& getModel() const { return _model;}
        inline ModelPtr& getModel() {return _model;}
    };


    //forward declarations for friendship purposes
    class MainController;
    class Application;

    class DisplayController : protected AbstractController
    {
        friend class MainController;
    private:
        DisplayController(const char* appPath, const LightManagerPtr& lights, const CameraManagerPtr& cameras)
        {
            //initialising display
            _displayer.reset(new Displayer(appPath, lights, cameras));
        }
        void runDisplay() const;

        inline const glimac::SDLWindowManager::SDL_WindowPtr& getWindowPtr()const {return _displayer->getWindowPtr();}
        inline const SDL_GLContext& getGLContext()const {return _displayer->getGLContext();}

    };

    class UIController : protected AbstractController
    {
        friend class MainController;
    private:
        bool runInterface() const;
    };

    class ComputeController : protected AbstractController
    {
        friend class MainController;
    private:
        ComputeController(const XUint worldWidth, const YUint worldLength)
        {
            //initialising Model
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


    class MainController : protected AbstractController
    {
        friend class Application;
    private:
        /* ComputeController needs to be initialiased first
        * before it initialises the model too
         * And the display uses a shared pointer to lights.
         */
        ComputeController _compCtrl;
        DisplayController _dispCtrl;
        UIController _uiCtrl;

    private:
        MainController(const char* appPath, const XUint worldWidth, const YUint worldLength):
                _compCtrl(worldWidth, worldLength),_dispCtrl(appPath, _model->getLightManagerPtr(), _model->getCameraManagerPtr()), _uiCtrl()  {}

        bool runLoop() const;
        void runApp() const;
    };

    class Application
    {
    public:
        typedef std::unique_ptr<MainController> ControllerPtr;
    private:
        static ControllerPtr _ctrl;
    public:

       static void init(const char* appPath, const XUint worldWidth, const YUint worldLength)
       {
          if( _ctrl )
              throw Exception(ExceptCode::ILLIGAL, 1, "Application already initialised.");
          _ctrl = ControllerPtr(new MainController(appPath, worldWidth, worldLength));
       }

       static void run()
       {
           if( !_ctrl )
               throw Exception(ExceptCode::ILLIGAL, 1, "Trying to run the application before initialisation.");
           else
               _ctrl->runApp();
       }
    };
}
#endif //WORLD_IMAKER_CONTROLLER_HPP
