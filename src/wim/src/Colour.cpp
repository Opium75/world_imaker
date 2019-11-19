//
// Created by piptouque on 15/11/2019.
//
#include "../include/Colour.hpp"

using namespace wim;

Colour::Colour(const float r, const float g, const float b) :
    Vec3D(colourValueFloat(r),colourValueFloat(g),colourValueFloat(b))
{

}

Colour::Colour(const Colour &c) : Vec3D(c)
{

}


Colour Colour::operator+(const Colour &c) const
{
    Colour sum;
    for(int i=0; i<_coord.length(); ++i)
    {
        sum._coord[i] = colourValueFloat(_coord[i] + c._coord[i]);
    }
    return sum;
}

Colour& Colour::operator+=(const Colour &c)
{
    for(int i=0; i<_coord.length(); ++i)
    {
        this->_coord[i] = colourValueFloat(_coord[i] + c._coord[i]);
    }
    return *this;
}

Colour Colour::average(const Colour &c) const
{
    return (*this + c)/2;
}

Colour& Colour::operator*(const float alpha)
{
    for(int i=0; i<_coord.length(); ++i)

        _coord[i] = colourValueFloat(_coord[i] * alpha);
    return *this;
}

Colour& Colour::operator/(const float alpha)
{
        if(alpha==0)
            throw std::string("Division by 0");
        else
            return (*this)*(1/alpha);
}

