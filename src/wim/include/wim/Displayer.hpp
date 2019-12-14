//
// Created by piptouque on 25/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYER_HPP
#define WORLD_IMAKER_DISPLAYER_HPP
#pragma  once


#include <GL/glew.h>
#include <imgui.h>

#include <glimac/SDLWindowManager.hpp>

#include "Exception.hpp"

#include "Cube.hpp"
#include "CubeStack.hpp"
#include "CubeWorld.hpp"

//default values for the SDL display window.
/*const char* DISP_WINDOW_NAME = "wim";
const float DEFAULT_WINDOW_WIDTH = 600.f;
const float DEFAULT_WINDOW_HEIGHT = 400.f;
*/
namespace wim {
    //Visitor class
    class Displayer {
    private:
        typedef std::shared_ptr<glimac::SDLWindowManager> WManagerPtr;
        WManagerPtr _manager;
    public:
        Displayer() : _manager()
        {
            this->initDisplay();
        }
        ~Displayer() = default;

        //const methods until I know what to do with them
        void display(const Cube &cube) const;
        void display(const CubeStack &stack) const;
        void display(const CubeWorld &world) const;

    private:
        //todo: WE'VE GOT TO HOLD ON TO WHAT WE'VE GOT
        //todo: IT DOESN'T EVEN MATTER IF WE MAKE IT OR NOT
       void initDisplay();
    };
}

#endif //WORLD_IMAKER_DISPLAYER_HPP