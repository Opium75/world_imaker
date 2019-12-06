//
// Created by piptouque on 25/11/2019.
//

//Already includes Cube, CubeStack, CubeWorld headers.
#include "../include/Displayer.hpp"

namespace wim {


    void Cube::display(const Displayer &disp) const {
        return disp.display(*this);
    }

    void CubeStack::display(const Displayer &disp) const {
        return disp.display(*this);
    }

    void CubeWorld::display(const Displayer &disp) const {
        return disp.display(*this);
    }

    void Displayer::display(const Cube &cube) const {
        std::cout << cube << std::endl;
    }

    void Displayer::display(const CubeStack &stack) const {
        std::cout << stack << std::endl;
    }

    void Displayer::display(const CubeWorld &world) const {
        std::cout << world(0, 0) << std::endl;
    }

    void Displayer::initDisplay() const
    {
        GLenum glewInitError = glewInit();
        if(GLEW_OK != glewInitError)
        {
            throw Exception(1, ExceptCode::INIT_ERROR, "Could not initialise glew.");
        }

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLEW Version:   " << glewGetString(GLEW_VERSION) << std::endl;

    }
}
