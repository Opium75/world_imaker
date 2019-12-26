//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_CUBEWORLD_HPP
#define WORLD_IMAKER_CUBEWORLD_HPP

#pragma once


#include <iostream>
#include <utility>
#include <Eigen/Dense>

#include "Types.hpp"
#include "Randomisable.hpp"
#include "CubeStack.hpp"


namespace wim
{

    class CubeWorld
    {
    public:
    private:
        typedef Eigen::Matrix<CubeStack, Eigen::Dynamic, Eigen::Dynamic> StackMatrix;
        StackMatrix _matrix;
    public:
        CubeWorld(const XUint width, const YUint length) : _matrix(width, length){}
        inline XUint getWidth() const {return _matrix.cols();}
        inline YUint getLength() const {return _matrix.rows();}

        inline CubeStack& operator()(const XUint x, const YUint y){
            //Eigen matrices are column-major.
            return _matrix(y,x);
        }
        inline const CubeStack& operator()(const XUint x, const YUint y) const {return _matrix(y,x);}

        CubeWorld& operator=(CubeWorld world)
        {
            std::swap(_matrix, world._matrix);
            return *this;
        }

        Cube& operator()(const XUint x, const YUint y, const ZUint z);

        static CubeWorld Random(const XUint width, const YUint length, const ZUint height);
    };
}

#endif //WORLD_IMAKER_CUBEWORLD_HPP
