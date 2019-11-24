//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_CUBEWORLD_HPP
#define WORLD_IMAKER_CUBEWORLD_HPP

#pragma once

#include <Eigen/Dense>
#include "Randomisable.hpp"
#include "CubeStack.hpp"

namespace wim
{
    class CubeWorld : Displayable // Randomisable<CubeWorld, int>
    {
    private:
        typedef size_t WorldWidth, WorldLength, WorldHeight;
        typedef Eigen::Matrix<CubeStack, Eigen::Dynamic, Eigen::Dynamic> StackMatrix;
        StackMatrix _matrix;
    public:
        //todo
        CubeWorld(const WorldWidth width, const WorldLength length);

        inline WorldWidth getWidth() const {return _matrix.cols();}
        inline WorldLength getLength() const {return _matrix.rows();}

        void display() const {};

        static CubeWorld Random(const WorldWidth width, const WorldLength length, const WorldHeight height);
    };
}

#endif //WORLD_IMAKER_CUBEWORLD_HPP
