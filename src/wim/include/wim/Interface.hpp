//
// Created by piptouque on 24/12/2019.
//

#ifndef WORLD_IMAKER_INTERFACE_HPP
#define WORLD_IMAKER_INTERFACE_HPP

#pragma once

#include <memory>

#include <SDL2/SDL.h>
#include <glimac/SDLWindowManager.hpp>

#include "CommunDisplay.hpp"
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
    private:

        inline const WindowManagerPtr& windowManager() const {return _displayer->windowManager();}
        inline WindowManagerPtr& windowManager() {return _displayer->windowManager();}


        inline bool pollEvent(SDL_Event &e) const {return this->windowManager()->pollEvent(e);}
        inline bool isKeyPressed(const SDL_Keycode key) const {return this->windowManager()->isKeyPressed(key);}

        void processState() const;
        bool processEvents() const;

        void processKeyboardUp(const SDL_Event& e) const;
        void processMouseMotion(const SDL_Event& e) const;
        void processMouseWheel(const SDL_Event& e) const;

        inline bool isMouseButtonPressed(uint32_t button) const
        {
            return this->windowManager()->isMouseButtonPressed(button);
        }

        void getRelativePosMouse(GLfloat& xRel, GLfloat& yRel) const;

        inline bool isRotating() const {return this->isMouseButtonPressed(SDL_BUTTON_MIDDLE);}

        void zoom(const GLint zoomDir) const;
        void rotate(const GLfloat xDeg, const GLfloat yDeg) const;

        void addPointLight(const PointLight& light) const;
        void addDirectionalLight(const DirectionalLight& light) const;

    public:
        bool run() const;
    };

    typedef std::unique_ptr<Interface> InterfacePtr;

}

#endif //WORLD_IMAKER_INTERFACE_HPP
