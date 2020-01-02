//
// Created by yoann on 17/12/2019.
//

#ifndef WORLD_IMAKER_CONTROLLER_HPP
#define WORLD_IMAKER_CONTROLLER_HPP

#pragma once

#include <memory>


#include "Exception.hpp"
#include "Displayer.hpp"
#include "Model.hpp"
#include "Interface.hpp"

namespace wim
{
    class AbstractController
    {
    protected:
        static ModelPtr _model;
        static DisplayerPtr _displayer;
        static InterfacePtr _interface;
    protected:

        inline const ModelPtr& model() const { return _model;}
        inline ModelPtr& model() {return _model;}

        inline const DisplayerPtr& displayer() const {return _displayer;}
        inline DisplayerPtr& displayer() {return _displayer;}

        inline const InterfacePtr& interface() const {return _interface;}
        inline InterfacePtr& interface() {return _interface;}
    };


    //forward declarations for friendship purposes
    class MainController;
    class Application;

    class DisplayController : protected AbstractController
    {
        friend class MainController;
    private:
        DisplayController() = default;
        void runDisplay() const;

        inline const WindowPtr& getWindowPtr()const {return _displayer->windowManager()->window();}
        inline const SDL_GLContext& getGLContext()const {return _displayer->getGLContext();}

        inline const LightManagerPtr& getLightManagerPtr() const {return _displayer->getLightManagerPtr();}
        inline const CameraManagerPtr& getCameraManagerPtr() const {return _displayer->getCameraManagerPtr();}
    };

    class InterfaceController : protected AbstractController
    {
        friend class MainController;
    private:
        bool runInterface() const;
    };

    class ComputeController : protected AbstractController
    {
        friend class MainController;
    private:
        ComputeController() = default;
        void runCompute() const
        {
            /* Compute calculations on Model
             * add cubes, etc..
             * depending on what was decided
             * by InterfaceController
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
        InterfaceController _interCtrl;

    private:
        MainController(const char* appPath, const XUint worldWidth, const YUint worldLength);
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
