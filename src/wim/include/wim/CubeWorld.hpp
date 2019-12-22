//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_CUBEWORLD_HPP
#define WORLD_IMAKER_CUBEWORLD_HPP

#pragma once

#include <iostream>
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
        //todo
        CubeWorld(const XUint width, const YUint length);

        inline XUint getWidth() const {return _matrix.cols();}
        inline YUint getLength() const {return _matrix.rows();}

        inline CubeStack& operator()(const XUint x, const YUint y) {return _matrix(x,y);}
        inline const CubeStack& operator()(const XUint x, const YUint y) const {return _matrix(x,y);}

        inline Cube& operator()(const XUint x, const YUint y, const ZUint z)
        {
            try
            {
                return _matrix(x,y).cube(z);
            }
            catch(Exception& e)
            {
               e.addMessageHead(std::string("In  CubeStack (")+std::to_string(x)+", "+std::to_string(y)+") :");
                throw;
            }
        }

        static CubeWorld Random(const XUint width, const YUint length, const ZUint height);
    };
}

#endif //WORLD_IMAKER_CUBEWORLD_HPP
