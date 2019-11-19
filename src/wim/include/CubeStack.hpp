//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_CUBESTACK_HPP
#define WORLD_IMAKER_CUBESTACK_HPP

#pragma once

#include <stack>
#include "Cube.hpp"

namespace wim
{
    ///A stack of Cube-class objects
    //In fact using a standard double-ended queue
    class CubeStack : protected Displayable
    {
    private:
        typedef std::deque<Cube> Stack;
        Stack _stack;
    public:
        CubeStack() = default;
        CubeStack(const CubeStack& cubeStack);
        ~CubeStack() = default;

        Cube& topCube();
        const Cube& topCube() const;

        //again, CubeStack will be Displayed through CubeWorld
        void display() const {};
    };
}

#endif //WORLD_IMAKER_CUBESTACK_HPP
