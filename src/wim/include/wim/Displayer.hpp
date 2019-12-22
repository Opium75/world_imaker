//
// Created by piptouque on 25/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYER_HPP
#define WORLD_IMAKER_DISPLAYER_HPP
#pragma  once

#include <memory>

//Use glew as static library
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

#include <glimac/SDLWindowManager.hpp>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include "Displayable.hpp"
#include "Exception.hpp"
#include "Light.hpp"
#include "Model.hpp"
#include "WidgetManager.hpp"
#include "SceneRenderer.hpp"

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
        typedef std::unique_ptr<glimac::SDLWindowManager> WindowManagerPtr;
        typedef std::unique_ptr<WidgetManager> WidgetManagerPtr;
        typedef std::unique_ptr<SceneRenderer> SceneRendererPtr;
        WindowManagerPtr _window;
        WidgetManagerPtr _widgets;
        SceneRendererPtr _renderer;

    public:
        Displayer(const char* appPath, const LightManagerPtr& lights, const CameraManagerPtr& cameras) :
            _window(std::make_unique<glimac::SDLWindowManager>(DISP_WINDOW_WIDTH, DISP_WINDOW_HEIGHT, DISP_WINDOW_NAME)),
            _widgets(std::make_unique<WidgetManager>()),
            _renderer(std::make_unique<SceneRenderer>(appPath, lights, cameras))
        {
            this->initDisplay();
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

        inline const glimac::SDLWindowManager::SDL_WindowPtr& getWindowPtr() const {return _window->getWindowPtr();};
        inline const SDL_GLContext& getGLContext() const {return _window->getGlContext();};

    private:
       void initDisplay(/*const char* appPath*/);
    };
}

#endif //WORLD_IMAKER_DISPLAYER_HPP
