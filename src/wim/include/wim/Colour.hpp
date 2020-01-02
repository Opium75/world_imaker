//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_COLOUR_HPP
#define WORLD_IMAKER_COLOUR_HPP

#pragma once

#include <iostream>
#include <glimac/glm.hpp>

#include "Exception.hpp"
#include "Vec3D.hpp"

namespace wim
{

    static const constexpr FloatType MAX_COLOUR_VALUE_FLOAT  = 1.f;
    static const constexpr FloatType MIN_COLOUR_VALUE_FLOAT = 0.f;
    //Colour inherits from Vec3D conceptually
    class Colour : public Vec3D {
    private:
        //The RGB values are inherited from the Vec3D<Float> class
    public:
        Colour() = default;
        Colour(const FloatType r, const FloatType g, const FloatType b);
        Colour(const Colour &c) = default;
        Colour(const Vec3D &vec);
        ~Colour() = default;

        Colour& operator=(const Colour &c);
        ///Returns first RGB value (red)
        inline FloatType& r(){return _coord.r;}
        inline FloatType r() const{return _coord.r;}

        //Returns second RGB value (green)
        inline FloatType& g(){return _coord.g;}
        inline FloatType g() const {return _coord.g;}

        //Returns third RGB value (blue)
        inline FloatType& b(){return _coord.b;}
        inline FloatType b() const {return _coord.b;}

        //Redefined Vec3D to jeep colour values in [0,1]
        Colour operator+(const Colour &c) const;
        Colour& operator+=(const Colour &c);

        Colour& operator*(const FloatType alpha);
        Colour& operator/(const FloatType alpha);

        ///Returns average of the current colour and c
        Colour average(const Colour &c) const;

        static Colour Random();
    };

    ///Format float value to colour value
    inline FloatType colourValueFloat(const FloatType value)
    {
        if(value>MAX_COLOUR_VALUE_FLOAT)
            return MAX_COLOUR_VALUE_FLOAT;
        else if(value<MIN_COLOUR_VALUE_FLOAT)
            return MIN_COLOUR_VALUE_FLOAT;
        return value;
    }
}



#endif //WORLD_IMAKER_COLOUR_HPP
