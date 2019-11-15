//
// Created by piptouque on 15/11/2019.
//
#include "../include/Colour.hpp"

using namespace wim;

Colour::Colour(const float r, const float g, const float b) :
    _rgb(colourValueFloat(r),colourValueFloat(g),colourValueFloat(b))
{

}

Colour::Colour(const Colour &c) : _rgb(c._rgb)
{

}

Colour& Colour::operator=(const Colour& c)
{
    this->_rgb = c._rgb;
    return *this;
}

Colour Colour::operator+(const Colour &c) const
{
    Colour sum;
    for(int i=0; i<_rgb.length(); ++i)
    {
        sum._rgb[i] = colourValueFloat(_rgb[i] + c._rgb[i]);
    }
    return sum;
}

Colour& Colour::operator+=(const Colour &c)
{
    for(int i=0; i<_rgb.length(); ++i)
    {
        this->_rgb[i] = colourValueFloat(_rgb[i] + c._rgb[i]);
    }
    return *this;
}

Colour Colour::average(const Colour &c) const
{
    return (*this + c)/2;
}

Colour& Colour::operator*(const float alpha)
{
    for(int i=0; i<_rgb.length(); ++i)
        _rgb[i] *= alpha;
    return *this;
}

Colour& Colour::operator/(const float alpha)
{
        if(alpha==0)
            throw std::string("Division by 0");
        else
            return (*this)*(1/alpha);
}

