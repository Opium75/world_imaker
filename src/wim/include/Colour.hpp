//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_COLOUR_HPP
#define WORLD_IMAKER_COLOUR_HPP

#pragma once

#include <iostream>
#include <glimac/glm.hpp>

#define _MAX_COLOUR_VALUE_FLOAT 1
#define _MIN_COLOUR_VALUE_FLOAT 0

namespace wim
{
    class Colour {
    private:
        ///triplet of floats
        glm::vec3 _rgb;
    public:
        Colour() = default;
        Colour(const float r, const float g, const float b);
        Colour(const Colour &c);
        ~Colour() = default;

        ///Returns first RGB value (red)
        inline float& r(){return _rgb.r;}
        inline float r() const{return _rgb.r;}

        //Returns second RGB value (green)
        inline float& g(){return _rgb.g;}
        inline float g() const {return _rgb.g;}

        //Returns third RGB value (blue)
        inline float& b(){return _rgb.b;}
        inline float b() const {return _rgb.b;}

        //Index bonds checked by glm
        inline float& operator[](size_t canal) {return _rgb[canal];}
        inline float operator[](size_t canal) const {return _rgb[canal];}


        Colour& operator=(const Colour &c);
        Colour operator+(const Colour &c) const;
        Colour& operator+=(const Colour &c);

        Colour& operator*(const float alpha);
        Colour& operator/(const float alpha);

        friend std::ostream& operator<<(std::ostream &stream, const Colour& c);

        ///Returns average of the current colour and c
        Colour average(const Colour &c) const;
    };

    inline std::ostream& operator<<(std::ostream &out, const Colour& c) { return out << c._rgb;}

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
