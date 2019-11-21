//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_COLOUR_HPP
#define WORLD_IMAKER_COLOUR_HPP

#pragma once

#include <iostream>
#include <glimac/glm.hpp>


#include "Vec3D.hpp"

#define _MAX_COLOUR_VALUE_FLOAT 1
#define _MIN_COLOUR_VALUE_FLOAT 0

namespace wim
{
    //Colour inherits from Vec3D conceptually
    class Colour : public Vec3D {
    private:
        //The RGB values are inherited from the Vec3D class
    public:
        Colour() = default;
        Colour(const float r, const float g, const float b);
        Colour(const Colour &c);
        ~Colour() = default;

        ///Returns first RGB value (red)
        inline float& r(){return _coord.r;}
        inline float r() const{return _coord.r;}

        //Returns second RGB value (green)
        inline float& g(){return _coord.g;}
        inline float g() const {return _coord.g;}

        //Returns third RGB value (blue)
        inline float& b(){return _coord.b;}
        inline float b() const {return _coord.b;}


        //Redefined Vec3D to jeep colour values in [0,1]
        Colour operator+(const Colour &c) const;
        Colour& operator+=(const Colour &c);

        Colour& operator*(const float alpha);
        Colour& operator/(const float alpha);

        ///Returns average of the current colour and c
        Colour average(const Colour &c) const;
    };


    ///Format float value to colour value
    inline float colourValueFloat(const float value)
    {
        if(value>_MAX_COLOUR_VALUE_FLOAT)
            return _MAX_COLOUR_VALUE_FLOAT;
        else if(value<_MIN_COLOUR_VALUE_FLOAT)
            return _MIN_COLOUR_VALUE_FLOAT;
        return value;
    }
}



#endif //WORLD_IMAKER_COLOUR_HPP
