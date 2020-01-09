//
// Created by piptouque on 24/12/2019.
//

#ifndef WORLD_IMAKER_INTERFACE_HPP
#define WORLD_IMAKER_INTERFACE_HPP

#pragma once

#include <memory>

#include <SDL2/SDL.h>
#include <glimac/SDLWindowManager.hpp>

#include "CommonDisplay.hpp"

#include "Types.hpp"
#include "Exception.hpp"

#include "Model.hpp"
#include "Displayer.hpp"

namespace wim
{

    class Interface {
        //todo
    private:
        ModelPtr _model;
        DisplayerPtr _displayer;

    public:
        Interface(const ModelPtr& model, const DisplayerPtr displayer) :
            _model(model), _displayer(displayer) {}

            bool run() const;
    private:
        inline const WindowManagerPtr& windowManager() const {return _displayer->windowManager();}
        inline WindowManagerPtr& windowManager() {return _displayer->windowManager();}

        inline const CursorPtr& cursor() const {return _model->cursor();}
        inline CursorPtr& cursor() {return _model->cursor();}


        inline bool pollEvent(SDL_Event& e) const {return this->windowManager()->pollEvent(e);}
        inline bool isKeyPressed(const SDL_Keycode key) const {return this->windowManager()->isKeyPressed(key);}

        bool processEvents() const;

        void processKeyboardUp(const SDL_Event& e) const;
        void processScene(const SDL_Event& e) const;
        void processCursor(const SDL_Event& e) const;
        void processCursorMoveKeyboard(const SDL_Event& e) const;
        void processCursorMoveMouse(const SDL_Event& e) const;
        void processSelect(const SDL_Event& e) const;
        void processCursorAction(const SDL_Event &e) const;

        void processMouseMotion(const SDL_Event& e) const;
        void processMouseWheel(const SDL_Event& e) const;
        void processMouseClick(const SDL_Event& e) const;

        inline bool isMouseButtonPressed(uint32_t button) const
        {
            return this->windowManager()->isMouseButtonPressed(button);
        }

        void getRelativePosMouse(GLfloat& xRel, GLfloat& yRel) const;

        bool readCubeIndex(Point3Uint& position, const GLint vX, const GLint vY) const;

        bool isRotating() const;

        void zoom(const GLint zoomDir) const;
        void rotate(const GLfloat xDeg, const GLfloat yDeg) const;

        void addPointLight(const PointLight& light) const;
        void addDirectionLight(const DirectionLight& light) const;
        void removePointLight(const SizeInt index) const;
        void removeDirectionLight(const SizeInt index) const;
        void setAmbiantLight(const AmbiantLight &light) const;

    };

    typedef std::unique_ptr<Interface> InterfacePtr;

}

#endif //WORLD_IMAKER_INTERFACE_HPP
