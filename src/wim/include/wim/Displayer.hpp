//
// Created by piptouque on 25/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYER_HPP
#define WORLD_IMAKER_DISPLAYER_HPP
#pragma  once

#include <memory>

#include "CommunDisplay.hpp"

#include <glimac/SDLWindowManager.hpp>

#include "Displayable.hpp"
#include "Exception.hpp"
#include "Model.hpp"
#include "WidgetManager.hpp"
#include "SceneRenderer.hpp"

#include "Cube.hpp"
#include "CubeStack.hpp"
#include "CubeWorld.hpp"


namespace wim {

    typedef std::unique_ptr<glimac::SDLWindowManager> WindowManagerPtr;
    typedef glimac::SDLWindowManager::SDL_WindowPtr WindowPtr;
    //default values for the SDL display window.
    static const float DISP_WINDOW_WIDTH = 600.f;
    static const float DISP_WINDOW_HEIGHT = 400.f;
    constexpr static const char* DISP_WINDOW_NAME = "wim"; //Look! We used constexpr!
    //Visitor class
    class Displayer {
    private:
        typedef std::unique_ptr<WidgetManager> WidgetManagerPtr;
        typedef std::unique_ptr<SceneRenderer> SceneRendererPtr;
        WindowManagerPtr _windows;
        WidgetManagerPtr _widgets;
        SceneRendererPtr _renderer;

    public:
        Displayer(const char* appPath, ModelPtr& model) :
            _windows(std::make_unique<glimac::SDLWindowManager>(DISP_WINDOW_WIDTH, DISP_WINDOW_HEIGHT, DISP_WINDOW_NAME)),
            _widgets(std::make_unique<WidgetManager>()),
            _renderer(std::make_unique<SceneRenderer>(appPath, model))
        {
        }
        ~Displayer() = default;

        //const methods until I know what to do with them
        void display(const Cube &cube, const XUint x, const YUint y, const ZUint z) const;
        void display(const CubeFloor &cubeFloor, const XUint x, const YUint y) const;
        void display(const CubeStack &cubeStack, const XUint x, const YUint y) const;
        void display(const CubeWorld &world) const;

        void displayAll(const Model& model) const;
        void displayModel(const Model& model) const;
        void displayWidgets() const;

        inline void addToRenderingStack(const Displayable &object, const Point3Int &anchor) const
        {
            _renderer->addToStack(Renderable(object, anchor));
        }

        inline const LightManagerPtr& getLightManagerPtr() const {return _renderer->lightManager();}
        inline const CameraManagerPtr& getCameraManagerPtr() const {return _renderer->cameraManager();}
        inline const SDL_GLContext& getGLContext() const {return _windows->getGlContext();};

        inline const WindowManagerPtr& windowManager() const {return _windows;};
        inline WindowManagerPtr& windowManager() {return _windows;};

    };

    typedef std::shared_ptr<Displayer> DisplayerPtr;
}

#endif //WORLD_IMAKER_DISPLAYER_HPP
