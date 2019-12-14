//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_CUBEWORLD_HPP
#define WORLD_IMAKER_CUBEWORLD_HPP

#pragma once

#include <iostream>
#include <Eigen/Dense>

#include "Displayable.hpp"
#include "Randomisable.hpp"
#include "CubeStack.hpp"


namespace wim
{
    class Displayer;

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

        inline CubeStack& operator()(const WorldWidth w, const WorldLength l) {return _matrix(w,l);}
        inline const CubeStack& operator()(const WorldWidth w, const WorldLength l) const {return _matrix(w,l);}

        //todo: define overload of operator() for Width, Length AND Height (w,l,h)

        void display(const Displayer& disp) const;

        static CubeWorld Random(const WorldWidth width, const WorldLength length, const WorldHeight height);
    };
}

#endif //WORLD_IMAKER_CUBEWORLD_HPP
