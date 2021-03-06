//
// Created by piptouque on 22/11/2019.
//

#ifndef WORLD_IMAKER_RANDOMISABLE_HPP
#define WORLD_IMAKER_RANDOMISABLE_HPP

#pragma once

#include <memory>
#include <ctime>

#include "Randomiser.hpp"

namespace wim
{
    //Singleton (so as not to have multiple generators for the same thing
    //Using time since Epoch by defualt as seed.
    /* class C is not used, but passing it as a template parameter
     * allows a Randomiser to be linked to every class
     * So that Colour ans Vector3D use different ones.
     */
    template <typename IntType>
    class IntRandomisable
    {
    public:
        typedef DefaultIntRandomiser<IntType> IntRandomiser;
        typedef std::unique_ptr<IntRandomiser> RandPointer;
    private:
        static RandPointer _rand;
    private:
        IntRandomisable()
        {
            static_assert(std::is_integral<IntType>::value);
        }
        static RandPointer& getRandomiser(const IntType lowest, const IntType highest, const Randomiser::SeedUInt seed = std::time(nullptr))
        {
            if( !_rand )
            {
                _rand = std::make_unique<IntRandomiser>(IntRandomiser(lowest, highest, seed));
            }
            else if ( !_rand->checkRange(lowest, highest))
            {
                //updating range of distribution.
                _rand->setRange(lowest, highest);
            }
            return _rand;
        }
    public:
        ~IntRandomisable() = default;
        static IntType Random(const IntType lowest, const IntType highest)
        {
           return getRandomiser(lowest, highest)->operator()();
        }
    };

    template <typename RealType>
    class RealRandomisable
    {
    public:
        typedef DefaultRealRandomiser<RealType> RealRandomiser;
        typedef std::unique_ptr<RealRandomiser> RandPointer;
    private:
        static RandPointer _rand;
    private:
        RealRandomisable()
        {
            static_assert(std::is_floating_point<RealType>::value);
        }
        static RandPointer& getRandomiser(const RealType lowest, const RealType highest, const Randomiser::SeedUInt seed = std::time(nullptr))
        {
            if( !_rand )
            {
                _rand = std::make_unique<RealRandomiser>(RealRandomiser(lowest, highest, seed));
            }
            else if ( !_rand->checkRange(lowest, highest) )
            {
                _rand->setRange(lowest, highest);
            }
            return _rand;
        }
    public:
        ~RealRandomisable() = default;
        static RealType Random(const RealType lowest, const RealType highest)
        {
            return getRandomiser(lowest, highest)->operator()();
        }

    };

    //Shortcut for random scalar:
    ///Brief; returns a single random scalar in closed interval [lowest, heighest] following uniform distribution
    template <typename T>
    T RandomScalar(const T& lowest = static_cast<T>(0), const T& highest= static_cast<T>(1))
    {
        //Function on scalar types only
        static_assert(std::is_scalar<T>::value);
        T scalar;
        if constexpr ( std::is_floating_point<T>::value )
            scalar = RealRandomisable<T>::Random(lowest, highest);
        else if constexpr ( std::is_integral<T>::value )
        {
            scalar = IntRandomisable<T>::Random(lowest,highest);
        }
        return scalar;
    }

    //Setting static attributes of template classes.
    template< typename RealType>
    typename RealRandomisable<RealType>::RandPointer RealRandomisable<RealType>::_rand = RandPointer(nullptr);
    template< typename IntType>
    typename IntRandomisable<IntType>::RandPointer IntRandomisable<IntType>::_rand = RandPointer(nullptr);
}

#endif //WORLD_IMAKER_RANDOMISABLE_HPP
