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
    template <class C, typename IntType>
    class IntRandomisable
    {
    public:
        typedef DefaultIntRandomiser<IntType> IntRandomiser;
        typedef std::unique_ptr<IntRandomiser> RandPointer;
    private:
        static RandPointer _rand;
    private:
        IntRandomisable() = default;
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

    template <class C, typename RealType>
    class RealRandomisable
    {
    public:
        typedef DefaultRealRandomiser<RealType> RealRandomiser;
        typedef std::unique_ptr<RealRandomiser> RandPointer;
    private:
        static RandPointer _rand;
    private:
        RealRandomisable() = default;
        static RandPointer& getRandomiser(const RealType lowest, const RealType highest, const Randomiser::SeedUInt seed = std::time(nullptr))
        {
            if( !_rand )
                _rand = std::make_unique<RealRandomiser>(RealRandomiser(lowest, highest, seed));
            else if ( !_rand->checkRange(lowest, highest))
            {
                //updating range of distribution.
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

    //Setting static attributes of template classes.
    template<class C, typename RealType>
    typename RealRandomisable<C,RealType>::RandPointer RealRandomisable<C,RealType>::_rand = RandPointer(nullptr);
    template<class C, typename IntType>
    typename IntRandomisable<C,IntType>::RandPointer IntRandomisable<C,IntType>::_rand = RandPointer(nullptr);
}

#endif //WORLD_IMAKER_RANDOMISABLE_HPP
