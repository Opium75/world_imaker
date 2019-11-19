//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_CUBEWORLD_HPP
#define WORLD_IMAKER_CUBEWORLD_HPP

#pragma once

#include <Eigen/Dense>

#include "CubeStack.hpp"

namespace wim
{
    class CubeWorld : Displayable
    {
    private:
        typedef Eigen::Matrix<CubeStack, Eigen::Dynamic, Eigen::Dynamic> StackMatrix;
        StackMatrix _matrix;
    public:
        //todo

        void display() const {};
    };
}

#endif //WORLD_IMAKER_CUBEWORLD_HPP
