//
// Created by piptouque on 25/12/2019.
//

#include "../include/wim/Interface.hpp"


namespace wim {

    bool Interface::run() const {
        bool loop = true;
        this->processState();
        loop = this->processEvents();
        return loop;
    }

    void Interface::processState() const
    {


    }

    void Interface::processScene(const SDL_Event &e) const {
        SizeInt width, length;
        switch (e.key.keysym.sym) {
            case SDLK_p:
                //Adding new pointlight
                this->addPointLight(PointLight::Random());
                break;
            case SDLK_m:
                //adding new directional light
                this->addDirectionLight(DirectionLight::Random());
                break;

            case SDLK_o:
                //ambiant lighting off
                this->setAmbiantLight(AmbiantLight(Colour(0, 0, 0)));
                break;
            case SDLK_i:
                // ambiant lighting on
                this->setAmbiantLight(AmbiantLight::Random());
                break;
            case SDLK_n:
                //changing World
                width = _model->world()->getWidth();
                length = _model->world()->getLength();
                *_model->world() = CubeWorld::Random(width, length);
            default:
                break;
        }
    }

    void Interface::processCursor(const SDL_Event &e) const
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_z:
                //move FOWARDS
                this->cursor()->moveZ(1);
                break;
            case SDLK_s:
                //move BACKWARDS
                this->cursor()->moveZ(-1);
                break;
            case SDLK_q:
                //move LEFT
                this->cursor()->moveX(-1);
                break;
            case SDLK_d:
                //move RIGHT
                this->cursor()->moveX(1);
                break;
            case SDLK_a:
                //move DOWN
                this->cursor()->moveY(-1);
                break;
            case SDLK_e:
                //move UP
                this->cursor()->moveY(1);
                break;
            default:
                break;
        }
    }

    void Interface::processKeyboardUp(const SDL_Event& e) const
    {
        this->processScene(e);
        this->processCursor(e);
    }

    void Interface::processMouseMotion(const SDL_Event& e) const
    {
        //rotation
        if( this->isRotating() )
        {
            GLfloat leftMotion, upMotion;
            upMotion = -e.motion.yrel;
            leftMotion = e.motion.xrel;
            this->rotate(upMotion, leftMotion);
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


    void Interface::processMouseClick(const SDL_Event& e) const
    {
        switch(e.button.button)
        {
            case SDL_BUTTON_LEFT:
                this->processSelect(e);
                break;

            default:
                break;
        }
    }

    void Interface::processSelect(const SDL_Event& e) const
    {
        Anchor position;
        GLint x,y;
        x = e.button.x;
        y = e.button.y;
        if( this->readCubeIndex(position, x, y) )
        {
            //Successfully found a cube.
            this->cursor()->setPosition(position);
        }
        else
        {
            //'twas not to be.
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
                    this->processMouseMotion(e);
                    break;

                case SDL_MOUSEWHEEL:
                    this->processMouseWheel(e);
                    break;

                case SDL_MOUSEBUTTONDOWN :
                    //
                    this->processMouseClick(e);
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

    void Interface::rotate(const GLfloat phi, const GLfloat theta) const
    {
        _displayer->getCameraManagerPtr()->rotate(phi, theta);
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
    void Interface::addDirectionLight(const DirectionLight &light) const
    {
        try
        {
            _model->addDirectionLight(light);
        }
        catch( Exception& e )
        {
            std::cout << e.what() << std::endl;
        }
    }

    void Interface::setAmbiantLight(const AmbiantLight &light) const
    {
        _model->lightManager()->setAmbiant(light);
    }

    bool Interface::readCubeIndex(Anchor& position, const GLint vX, const GLint vY) const
    {
        return _displayer->readCubeIndex(position, vX, vY);
    }
}