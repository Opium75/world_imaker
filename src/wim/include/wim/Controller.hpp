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
#include "Interface.hpp"

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
        DisplayController(const char* appPath)
        {
            //initialising display
            _displayer.reset(new Displayer(appPath));
        }
        void runDisplay() const;

        inline const glimac::SDLWindowManager::SDL_WindowPtr& getWindowPtr()const {return _displayer->getWindowPtr();}
        inline const SDL_GLContext& getGLContext()const {return _displayer->getGLContext();}

        inline const LightManagerPtr& getLightManagerPtr() const {return _displayer->getLightManagerPtr();}
        inline const CameraManagerPtr& getCameraManagerPtr() const {return _displayer->getCameraManagerPtr();}
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
        ComputeController(const XUint worldWidth, const YUint worldLength, const LightManagerPtr& lights, const CameraManagerPtr& cameras)
        {
            //initialising Model
            _model.reset(new Model(worldWidth, worldLength, lights, cameras));
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
        /* DisplayController needs to be initialised first
         * to set-up the OpenGL, and SDL context,
         * as well as lights and cameras.
         */

        DisplayController _dispCtrl;
        ComputeController _compCtrl;
        UIController _uiCtrl;

    private:
        MainController(const char* appPath, const XUint worldWidth, const YUint worldLength):
                _dispCtrl(appPath),
                _compCtrl(worldWidth, worldLength,
                        _dispCtrl.getLightManagerPtr(),
                        _dispCtrl.getCameraManagerPtr()),
                _uiCtrl()  {}

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
