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

    void ProceduralGenerator::buildCubeRbf(CubeRBFPtr& cubeRbf, const SelectionPtr& selection) const
    {
  /*      ListSelectedPtr& listSelected = selection->selected();
        VecPoint<XUint> vecPoint;
        VecScalar<FloatType> vecWeight;
        VecValues<Cube> vecValues;

        this->loadPoints(cubeRbf->vecPoint(), listSelected);

        this->loadPoints(vecPoint, listSelected);
        this->loadWeights(vecWeight, listSelected);
        this->loadValues(vecValues, listSelected);
*/
        this->buildRbf<Cube, XUint, FloatType>(cubeRbf, selection);
    }

}