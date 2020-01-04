//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_CUBEWORLD_HPP
#define WORLD_IMAKER_CUBEWORLD_HPP

#pragma once


#include <iostream>
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
        CubeWorld(const XUint width, const ZUint length);
        inline XUint getWidth() const {return _matrix.rows();}
        inline ZUint getLength() const {return _matrix.cols();}

        inline CubeStack& operator()(const XUint x, const ZUint z) {return _matrix(x,z);}
        inline const CubeStack& operator()(const XUint x, const ZUint z) const {return _matrix(x,z);}

        void add(const Cube& cube, const Point3Uint& position);
        void erase(const Point3Uint& position);

        void extrude(const Point3Uint& position);
        void dig(const Point3Uint& position);

        CubeWorld& operator=(CubeWorld world);

        Cube& operator()(const XUint x, const YUint y, const ZUint z);
        Cube& operator()(const Point3Uint& position);

        ///brief: no exception version of operator()
        bool findCube(CubePtr& cubePtr, const Point3Uint& position);
        bool isOccupied(const Point3Uint& position) const;
        bool isHigherStackEmpty(const XUint x, const FloorIndex floor, const ZUint z) const;
        bool isLowerStackEmpty(const XUint x, const FloorIndex floor, const ZUint z) const;

        void swapSpaces(const Point3Uint &position1, const Point3Uint &position2);


        static CubeWorld Random(const XUint width, const YUint length);
    };

    typedef std::shared_ptr<CubeWorld> WorldPtr;
}

#endif //WORLD_IMAKER_CUBEWORLD_HPP
