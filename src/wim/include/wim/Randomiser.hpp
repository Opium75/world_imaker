//
// Created by piptouque on 21/11/2019.
//

#ifndef WORLD_IMAKER_RANDOMISER_HPP
#define WORLD_IMAKER_RANDOMISER_HPP

#pragma once

#include <random>
#include <functional>
#include <iostream>
//#include <chrono>

namespace wim
 {

    /*So, finding room for template classes was actually pretty easy.*/
    class Randomiser
    {
    public:
        //Public typedef
        typedef std::default_random_engine RandomEngine, RandomGenerator;
        typedef RandomEngine::result_type SeedUInt;
    protected:
        SeedUInt _seed;
        RandomEngine _engine;
    public:
        /* That's the abstract interface for Randomisers
         * Offers nothing because Randomisers have different template parameters
         * and return types (cannot generalise).
         * */
        Randomiser(const SeedUInt seed)  : _seed(seed), _engine(seed)
        {

        }
        ~Randomiser() = default;
        //todo ?
    };

template <typename IntType>
    class DefaultIntRandomiser : public Randomiser
    {
    protected:
        typedef std::uniform_int_distribution<IntType> RandomDistribution;
    private:
        RandomDistribution _distrib;
    public:
        DefaultIntRandomiser() = default;
        DefaultIntRandomiser(const IntType highest, const SeedUInt seed = RandomEngine::default_seed) : Randomiser(seed), _distrib(highest)
        {
            //int value > 0 checked by lib
        }
        DefaultIntRandomiser(const IntType lowest, const IntType highest, const SeedUInt seed = RandomEngine::default_seed) : Randomiser(seed), _distrib(lowest, highest)
        {

        }
        inline IntType getLowest() const {return _distrib.a();}
        inline IntType getHighest() const {return _distrib.b();}

        inline bool checkRange(const IntType lowest, const IntType highest) {return (lowest == getLowest()) && (highest == getHighest());}
        inline void setRange(const IntType lowest, const IntType highest)
        {
            _distrib = RandomDistribution(lowest, highest);
        }
        ///Returns random inr in [lowest, highest] according to distrib
        IntType operator()()
        {
            return _distrib(_engine);
        }
    };

template <typename RealType>
    class DefaultRealRandomiser : public Randomiser
    {
    protected:
        typedef std::uniform_real_distribution<RealType> RandomDistribution;

    private:
        RandomDistribution _distrib;
    public:
        DefaultRealRandomiser() = default;
        DefaultRealRandomiser(const RealType highest, const SeedUInt seed = RandomEngine::default_seed) : Randomiser(seed),  _distrib( highest)
        {

        }
        DefaultRealRandomiser(const RealType lowest, const RealType highest, const SeedUInt seed = RandomEngine::default_seed) : Randomiser(seed), _distrib(lowest, highest)
        {

        }
        inline RealType getLowest() const {return _distrib.a();}
        inline RealType getHighest() const {return _distrib.b();}

        inline bool checkRange(const RealType lowest, const RealType highest) {return (lowest == getLowest()) && (highest == getHighest());}
        inline void setRange(const RealType lowest, const RealType highest)
        {
            _distrib = RandomDistribution(lowest, highest);
        }

        ///Returns random real number in [lowest, highest] according to distrib
        RealType operator()()
        {
            return _distrib(_engine);
        }
    };
}

#endif //WORLD_IMAKER_RANDOMISER_HPP
