//
// Created by piptouque on 19/11/2019.
//

#include "../include/wim/CubeWorld.hpp"


namespace wim
{
    Cube& CubeWorld::operator()(const XUint x, const YUint y, const ZUint z)
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

    CubeWorld CubeWorld::Random(const XUint width, const YUint length, const ZUint height) {
        CubeWorld world(width, length);
        for (size_t i = 0; i < width; ++i) {
            for (size_t j = 0; j < length; ++j) {
                CubeStack rand = CubeStack::Random(height, 0, height);
                world._matrix(i, j) = rand;
            }
        }
        return world;
    }

}