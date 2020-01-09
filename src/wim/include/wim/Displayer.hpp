//
// Created by piptouque on 25/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYER_HPP
#define WORLD_IMAKER_DISPLAYER_HPP
#pragma  once

#include <memory>

#include "CommonDisplay.hpp"

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

    //default values for the SDL display window.
    static constexpr float DEFAULT_DISP_WINDOW_WIDTH = 600.f;
    static constexpr float DEFAULT_DISP_WINDOW_HEIGHT = 400.f;
    static constexpr const char* DISP_WINDOW_NAME = "wim";
    //Visitor class
    class Displayer {
    private:
        typedef std::unique_ptr<WidgetManager> WidgetManagerPtr;
        typedef std::unique_ptr<SceneRenderer> SceneRendererPtr;
        WindowManagerPtr _windows;
        WidgetManagerPtr _widgets;
        SceneRendererPtr _renderer;

    public:
        Displayer(const char* appPath, ModelPtr& model);
        ~Displayer() = default;

        void displayAll(const Model& model) const;

        bool readCubeIndex(Point3Uint& position, const GLint vX, const GLint vY) const;

        inline const LightManagerPtr& getLightManagerPtr() const {return _renderer->lightManager();}
        inline const CameraManagerPtr& getCameraManagerPtr() const {return _renderer->cameraManager();}
        inline const SDL_GLContext& getGLContext() const {return _windows->getGlContext();};

        inline const WindowManagerPtr& windowManager() const {return _windows;};
        inline WindowManagerPtr& windowManager() {return _windows;};

    private:
        //const methods until I know what to do with them
        void display(const Cursor& cursor) const;
        void display(const Cube &cube) const;
        void display(const CubeFloor &cubeFloor) const;
        void display(const CubeStack &cubeStack) const;
        void display(const CubeWorld &world) const;

        void displayModel(const Model& model) const;
        void displayWidgets() const;

        void addToRenderingStacks(const Displayable &object, const Anchor &anchor, const FloatType rotX=0, const FloatType rotY=0) const;
        void addToRenderingStacks(const BaseQuad &baseQuad, const XUint x, const ZUint z) const;
        void addToRenderingStacks(const Cursor &cursor, const Anchor& anchor, const bool isCursor) const;
    };

    typedef std::shared_ptr<Displayer> DisplayerPtr;
}

#endif //WORLD_IMAKER_DISPLAYER_HPP
