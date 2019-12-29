//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_CUBEWORLD_HPP
#define WORLD_IMAKER_CUBEWORLD_HPP

#pragma once


#include <iostream>
#include <utility>
#include <memory>
#include <Eigen/Dense>

#include "Types.hpp"
#include "Randomisable.hpp"
#include "TextureManager.hpp"
#include "CubeStack.hpp"
#include "Cube.hpp"

namespace wim
{

    class CubeWorld
    {
    public:
    private:
        typedef Eigen::Matrix<CubeStack, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> StackMatrix;
        StackMatrix _matrix;
    public:
        CubeWorld() = default;
        CubeWorld(const XUint width, const YUint length) :
            _matrix(width,length) {}
        inline XUint getWidth() const {return _matrix.rows();}
        inline YUint getLength() const {return _matrix.cols();}

        inline CubeStack& operator()(const XUint x, const YUint y)
        {
            return _matrix(x,y);
        }
        inline const CubeStack& operator()(const XUint x, const YUint y) const
        {
            return _matrix(x,y);
        }

        CubeWorld& operator=(CubeWorld world)
        {
            std::swap(_matrix, world._matrix);
            return *this;
        }
        Cube& operator()(const XUint x, const YUint y, const ZUint z);


        static CubeWorld Random(const XUint width, const YUint length);
    };
}

#endif //WORLD_IMAKER_CUBEWORLD_HPP
