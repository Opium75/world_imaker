//
// Created by piptouque on 06/01/2020.
//

#ifndef WORLD_IMAKER_RADIALFUNCTOR_HPP
#define WORLD_IMAKER_RADIALFUNCTOR_HPP

#pragma once

#include <cmath>
#include <string>
#include <iostream>

#include "Types.hpp"
#include "Vec3D.hpp"

namespace wim
{

    template<typename T>
    using Point = TVec3D<T>;

    static constexpr SizeInt NB_RADIALMETHODS = 4;
    enum class RadialMethod : SizeInt
    {
        LINEAR,
        MULTIQUADRIC,
        INVERT_MULTIQUADRIC,
        GAUSSIAN
    };

    template<typename T, typename D>
    class DistanceFunctor
    {
    public:
        template<SizeInt n=2>
        D operator()(const Point<T>& p1, const Point<T>& p2) const
        {
            return p1.template distance<D,n>(p2);
        }
    };


    template<typename D>
    class RadialFunctor
    {
    protected:
        D _epsilon;
    public:
        RadialFunctor(const D epsilon= static_cast<D>(1)) : _epsilon(epsilon) {}
        virtual D operator()(const D distance) const {return distance;};
    };

    template<typename D>
    class LinearFunctor : public RadialFunctor<D>
    {
    public:
        D operator()(const D distance) const override
        {
            return distance;
        }
    };

    template <typename D>
    class MultiquadricFunctor : public RadialFunctor<D>
    {
    public:
        MultiquadricFunctor(const D epsilon) : RadialFunctor<D>(epsilon){}
        D operator()(const D distance) const override
        {
            return static_cast<D>(
                    std::sqrt(
                            static_cast<double>(
                            static_cast<D>(1) +
                            (this->_epsilon*distance)*(this->_epsilon*distance)
                            )
                            )
                    );
        }
    };

    template<typename D>
    class InvertMultiquadricFunctor : public RadialFunctor<D>
    {
    public:
        InvertMultiquadricFunctor(const D epsilon) : RadialFunctor<D>(epsilon) {}
        D operator()(const D distance) const override
        {
            return static_cast<D>(
                    std::sqrt(1./
                            static_cast<double>(
                                    static_cast<D>(1) +
                                    (this->_epsilon*distance)*(this->_epsilon*distance)
                            )
                    )
            );
        }
    };

    template <typename D>
    class GaussianFunctor : public RadialFunctor<D>
    {
    public:
        GaussianFunctor(const D epsilon) : RadialFunctor<D>(epsilon) {}
        D operator()(const D distance) const override
        {
            return static_cast<D>(
                    std::exp(
                            -static_cast<double>(
                            this->_epsilon*distance*distance)
                    )
                    );
        }
    };

    template<typename D>
    class RadialFactory
    {
    public:
        RadialFunctor<D> makeRadial(const RadialMethod method, const D epsilon = static_cast<D>(1))
        {
            switch(method)
            {
                case RadialMethod::LINEAR :
                    return LinearFunctor<D>();
                case RadialMethod::MULTIQUADRIC:
                    return MultiquadricFunctor<D>(epsilon);
                case RadialMethod::INVERT_MULTIQUADRIC:
                    return InvertMultiquadricFunctor<D>(epsilon);
                case RadialMethod::GAUSSIAN:
                    return GaussianFunctor<D>(epsilon);
                default:
                    return LinearFunctor<D>();
            }
        }
    };

    RadialMethod getNextMethod(const RadialMethod method);
    std::string toString(const RadialMethod method);
    std::ostream& operator<<(std::ostream& out, const RadialMethod method);
}
#endif //WORLD_IMAKER_RADIALFUNCTOR_HPP
