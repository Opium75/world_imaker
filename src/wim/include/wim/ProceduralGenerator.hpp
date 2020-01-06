//
// Created by piptouque on 06/01/2020.
//

#ifndef WORLD_IMAKER_PROCEDURALGENERATOR_HPP
#define WORLD_IMAKER_PROCEDURALGENERATOR_HPP

#pragma once

#include <memory>

#include "Types.hpp"
#include "OmegaFunctor.hpp"

#include "Cube.hpp"


namespace wim
{
    typedef OmegaFunctor<Cube, XUint, FloatType> CubeRBF;
    typedef OmegaFunctorPtr<Cube, XUint, FloatType> CubeRBFPtr;

    class ProceduralGenerator
    {
    private:
        CubeRBFPtr _cubeRbf;
    public:
        ProceduralGenerator();
    };

    typedef std::unique_ptr<ProceduralGenerator> ProceduralGeneratorPtr;
}
#endif //WORLD_IMAKER_PROCEDURALGENERATOR_HPP
