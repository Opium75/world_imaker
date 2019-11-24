//
// Created by piptouque on 19/11/2019.
//

#include "../include/Vec3D.hpp"

using namespace wim;

Vec3D::Vec3D(const FloatType x, const FloatType y, const FloatType z) :
        _coord(x,y,z)
{

}

Vec3D::Vec3D(const Vec3D& vec) : _coord(vec._coord)
{

}

Vec3D::Vec3D(const glm::vec3 &coord) : _coord(coord)
{

}

Vec3D& Vec3D::operator=(const Vec3D& vec)
{
    this->_coord = vec._coord;
    return *this;
}

Vec3D Vec3D::operator+(const Vec3D& vec) const
{
    return Vec3D( this->_coord + vec._coord );
}

Vec3D& Vec3D::operator+=(const Vec3D& vec)
{
    this->_coord += vec._coord;
    return *this;
}

Vec3D& Vec3D::operator*(const FloatType alpha)
{
    for (int i = 0; i < _coord.length(); ++i)
        _coord[i] *= alpha;
    return *this;
}

Vec3D& Vec3D::operator/(const FloatType alpha)
{
    if (alpha == 0)
        throw std::domain_error("Division by O");
    else
        return (*this)*(1/alpha);
}

Vec3D Vec3D::Random(const FloatType lowest, const FloatType highest)
{
    FloatType x,y,z;
    x = RealRandomisable<FloatType>::Random(lowest, highest);
    y = RealRandomisable<FloatType>::Random(lowest, highest);
    z =  RealRandomisable<FloatType>::Random(lowest, highest);
   return Vec3D(x,y,z);
}