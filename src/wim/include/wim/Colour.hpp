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

#define _MAX_COLOUR_VALUE_FLOAT 1
#define _MIN_COLOUR_VALUE_FLOAT 0

namespace wim
{
    //Colour inherits from Vec3D conceptually
    class Colour : public Vec3D {
    private:
        typedef float FloatType;
        //The RGB values are inherited from the Vec3D<Float> class
    public:
        Colour() = default;
        Colour(const FloatType r, const FloatType g, const FloatType b);
        Colour(const Colour &c);
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
    inline Vec3D::ValueType colourValueFloat(const Vec3D::ValueType value)
    {
        if(value>_MAX_COLOUR_VALUE_FLOAT)
            return _MAX_COLOUR_VALUE_FLOAT;
        else if(value<_MIN_COLOUR_VALUE_FLOAT)
            return _MIN_COLOUR_VALUE_FLOAT;
        return value;
    }
}



#endif //WORLD_IMAKER_COLOUR_HPP
