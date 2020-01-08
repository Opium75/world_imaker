//
// Created by piptouque on 06/06/2066.
//

#ifndef WORLD_IMAKER_PROCEDURALGENERATOR_HPP
#define WORLD_IMAKER_PROCEDURALGENERATOR_HPP

#pragma once

#include <memory>

#include "Types.hpp"
#include "RBF.hpp"

#include "Cube.hpp"
#include "CubeWorld.hpp"
#include "Selection.hpp"

namespace wim
{
    typedef RBF<Cube, XUint, FloatType> CubeRBF;
    typedef RBFPtr<Cube, XUint, FloatType> CubeRBFPtr;

    class ProceduralGenerator
    {
    private:
        CubeRBFPtr _cubeRbf;
    public:
        ProceduralGenerator();
        void build(const SelectionPtr& selection, const RadialMethod method=RadialMethod::LINEAR);


        void buildCubeRbf(CubeRBFPtr& cubeRbf, const SelectionPtr& selection, const RadialMethod method) const;
        void setCubeRadialMethod(const RadialMethod method);

        template<class C, typename T, typename D>
        void buildRbf(RBFPtr<C,T,D>& rbf, const SelectionPtr& selection, const RadialMethod method) const
        {
            ListSelectedPtr& listSelected = selection->selected();
            VecPoint<T> points;
            VecScalar<D> weights;
            VecValues<C> values;

            this->loadPoints(points, listSelected);
            this->loadWeights(weights, listSelected);
            this->loadValues(values, listSelected);
            rbf.reset(new RBF<C,T,D>(points, weights, values, method));
        }

        template<typename T>
        void loadPoints(VecPoint<T>& points, const ListSelectedPtr& selected) const
        {
            points.resize(selected.size());
            for( SizeInt i=0; i<(SizeInt)points.size(); ++i )
                points(i) = selected.at(i)->position();
        }

        template<typename D>
        void loadWeights(VecScalar<D>& weights, const ListSelectedPtr& selected) const
        {
            weights.resize(selected.size());
            for( SizeInt i=0; i<(SizeInt)weights.size(); ++i )
                weights(i) = selected.at(i)->weight();
        }

        template<typename C>
        void loadValues(VecValues<C>& values, const ListSelectedPtr& selected) const
        {
            values.resize(selected.size());
            for( SizeInt i=0; i<(SizeInt)values.size(); ++i)
            {
                //todo: find a way to handle Cubes as Selectables
               values(i) = (C)*(selected.at(i)->object());
            }
        }

    };

    typedef std::unique_ptr<ProceduralGenerator> ProceduralGeneratorPtr;
}
#endif //WORLD_IMAKER_PROCEDURALGENERATOR_HPP
