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

    void ProceduralGenerator::build(const SelectionPtr& selection, const RadialMethod method)
    {
        this->buildCubeRbf(_cubeRbf, selection, method);
    }

    CubeRBF& ProceduralGenerator::getCubeRBF() const
    {
        return *_cubeRbf;
    }

    void ProceduralGenerator::buildCubeRbf(CubeRBFPtr& cubeRbf, const SelectionPtr& selection, const RadialMethod method) const
    {
        this->buildRbf<Cube, XUint, FloatType>(cubeRbf, selection, method);
    }

    void ProceduralGenerator::setCubeRadialMethod(const wim::RadialMethod method)
    {
        _cubeRbf->setRadialMethod(method);
    }

}