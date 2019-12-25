//
// Created by piptouque on 25/12/2019.
//

#include "../include/wim/Interface.hpp"


namespace wim {

    bool Interface::run() const
    {
        bool loop = true;
        this->processState();
        loop = this->processEvents();
        return loop;
    }

    void Interface::processState() const
    {
        //zoom
        int zoomDir = this->isZooming();
        if( zoomDir )
        {
            this->zoom(zoomDir);
        }


    }

    void Interface::processMouseMotion(const SDL_Event& e) const
    {
        //rotation
        if( this->isRotating() )
        {
            GLfloat xMotion, yMotion;
            xMotion = e.motion.xrel;
            yMotion = e.motion.yrel;
            this->rotate(xMotion, yMotion);
        }
    }

    bool Interface::processEvents() const {

        bool loop = true;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            //ImGui does its thing
           // ImGui_ImplSDL2_ProcessEvent(&e);

            switch (e.type) {
                case SDL_QUIT :
                    loop = false;
                    break;

                case SDL_KEYDOWN  :
                    //Function in Controller or switch and case ?
                    break;

                case SDL_MOUSEMOTION :
                    //Get the position
                    this->processMouseMotion(e);
                    break;

                case SDL_MOUSEWHEEL:

                case SDL_MOUSEBUTTONDOWN :
                    //
                    break;

                default :
                    break;
            }
        }
        return loop;
    }


    void Interface::getRelativePosMouse(GLfloat& xRel, GLfloat& yRel) const
    {
        int windowWidth, windowHeight;
        this->windowManager()->getWindowSize(windowWidth, windowHeight);
        glm::ivec2 mousePos = this->windowManager()->getMousePosition();
        xRel = (mousePos.x - windowWidth/2)/(GLfloat)windowWidth;
        yRel = (mousePos.y - windowHeight/2)/(GLfloat)windowHeight;
    }

    void Interface::zoom(const GLint zoomDir) const
    {
        _displayer->getCameraManagerPtr()->zoom(zoomDir);
    }

    void Interface::rotate(const GLfloat xDeg, const GLfloat yDeg) const
    {
        _displayer->getCameraManagerPtr()->rotate(yDeg,xDeg);
    }
}