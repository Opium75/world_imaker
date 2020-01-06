//
// Created by piptouque on 15/11/2019.
//
#include "../include/wim/Colour.hpp"

namespace  wim
{

    Colour::Colour(const FloatType r, const FloatType g, const FloatType b) :
            Vec3D(colourValueFloat(r), colourValueFloat(g), colourValueFloat(b)) {

    }

    Colour::Colour(const Vec3D &vec) : Colour(vec.x(), vec.y(), vec.z())
    {

    }

    Colour& Colour::operator=(const Colour &c)
    {
        _coord = c._coord;
        return *this;
    }

    Colour Colour::operator+(const Colour &c) const {
        Colour sum;
        for (int i = 0; i < _coord.length(); ++i) {
            sum._coord[i] = colourValueFloat(_coord[i] + c._coord[i]);
        }
        return sum;
    }

    Colour &Colour::operator+=(const Colour &c) {
        for (int i = 0; i < _coord.length(); ++i) {
            this->_coord[i] = colourValueFloat(_coord[i] + c._coord[i]);
        }
        return *this;
    }

    Colour Colour::average(const Colour &c) const {
        return (*this + c) / 2;
    }

    Colour& Colour::operator*(const FloatType alpha) {
        for (int i = 0; i < _coord.length(); ++i)

            _coord[i] = colourValueFloat(_coord[i] * alpha);
        return *this;
    }

    Colour& Colour::operator/(const FloatType alpha) {
        if (alpha == 0)
            throw Exception(ExceptCode::DOMAIN_ERROR, 1, "Trying to divide by O.");
        else
            return (*this) * (1 / alpha);
    }

    Colour Colour::Random() {
        return Colour(Vec3D::Random(MIN_COLOUR_VALUE_FLOAT, MAX_COLOUR_VALUE_FLOAT));
    }

}