//
// Created by piptouque on 06/01/2020.
//

#include "../include/wim/ProceduralGenerator.hpp"

namespace wim
{
    ProceduralGenerator::ProceduralGenerator() :
        _cubeRbf(std::make_unique<CubeRBF>())
    {

    }
}