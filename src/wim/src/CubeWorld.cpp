//
// Created by piptouque on 19/11/2019.
//

#include "../include/wim/CubeWorld.hpp"


namespace wim
{


//todo

    CubeWorld::CubeWorld(const XUint width, const YUint length) : _matrix(width, length) {
    }

    CubeWorld CubeWorld::Random(const XUint width, const YUint length, const ZUint height) {
        CubeWorld world(width, length);
        for (size_t i = 0; i < width; ++i) {
            for (size_t j = 0; j < length; ++j) {
                world._matrix(i, j) = CubeStack::Random(height, 0, height);
            }
        }
        return world;
    }

}