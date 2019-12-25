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

        void processState() const;
        bool processEvents() const;

        void processMouseMotion(const SDL_Event& e) const;

        inline bool isMouseButtonPressed(uint32_t button) const
        {
            return this->windowManager()->isMouseButtonPressed(button);
        }

        void getRelativePosMouse(GLfloat& xRel, GLfloat& yRel) const;

        inline int isZooming() const {return (this->isMouseButtonPressed(SDL_BUTTON_LEFT) - this->isMouseButtonPressed(SDL_BUTTON_RIGHT));}
        inline bool isRotating() const {return this->isMouseButtonPressed(SDL_BUTTON_MIDDLE);}

        void zoom(const GLint zoomDir) const;
        void rotate(const GLfloat xDeg, const GLfloat yDeg) const;


    public:
        bool run() const;
    };

    typedef std::unique_ptr<Interface> InterfacePtr;

}

#endif //WORLD_IMAKER_INTERFACE_HPP
