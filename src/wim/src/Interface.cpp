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


    }

    void Interface::processKeyboardUp(const SDL_Event& e) const
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_p:
                //Adding new pointlight
                this->addPointLight(PointLight::Random());
                break;
            case SDLK_m:
                //adding new directional light
                this->addDirectionalLight(DirectionalLight::Random());
            default:
                break;
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


    void Interface::processMouseWheel(const SDL_Event& e) const
    {
        int zoomDir = e.wheel.y;
        if( zoomDir )
        {
            this->zoom(zoomDir);
        }
    }

    bool Interface::processEvents() const {

        bool loop = true;

        SDL_Event e;
        while (this->pollEvent(e)) {
            //ImGui does its thing
           // ImGui_ImplSDL2_ProcessEvent(&e);

            switch (e.type) {
                case SDL_QUIT :
                    loop = false;
                    break;

                case SDL_KEYUP  :
                    //Function in Controller or switch and case ?
                    this->processKeyboardUp(e);
                    break;

                case SDL_MOUSEMOTION :
                    //Get the position
                    this->processMouseMotion(e);
                    break;

                case SDL_MOUSEWHEEL:
                    this->processMouseWheel(e);
                    break;

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

    void Interface::addPointLight(const PointLight &light) const
    {
        try
        {
            _model->addPointLight(light);
        }
        catch( Exception& e )
        {
            std::cout << e.what() << std::endl;
        }
    }
    void Interface::addDirectionalLight(const DirectionalLight &light) const
    {
        try
        {
            _model->addDirectionalLight(light);
        }
        catch( Exception& e )
        {
            std::cout << e.what() << std::endl;
        }
    }
}