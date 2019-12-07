//
// Created by piptouque on 25/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYER_HPP
#define WORLD_IMAKER_DISPLAYER_HPP
#pragma  once


#include <GL/glew.h>

#include "Exception.hpp"

#include "Cube.hpp"
#include "CubeStack.hpp"
#include "CubeWorld.hpp"

namespace wim {
    //Visitor class
    class Displayer {
    public:
        Displayer() = default;
        ~Displayer() = default;

        //const methods until I know what to do with them
        void display(const Cube &cube) const;
        void display(const CubeStack &stack) const;
        void display(const CubeWorld &world) const;

    private:
        //todo: WE'VE GOT TO HOLD ON TO WHAT WE'VE GOT
        //todo: IT DOESN'T EVEN MATTER IF WE MAKE IT OR NOT
       void initDisplay() const;
    };
}

#endif //WORLD_IMAKER_DISPLAYER_HPP
