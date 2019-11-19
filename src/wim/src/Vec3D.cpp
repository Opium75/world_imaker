//
// Created by piptouque on 19/11/2019.
//

#include "../include/Vec3D.hpp"

using namespace wim;

Vec3D::Vec3D(const float x, const float y, const float z) :
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

Vec3D& Vec3D::operator*(const float alpha)
{
    for (int i = 0; i < _coord.length(); ++i)
        _coord[i] *= alpha;
    return *this;
}

Vec3D& Vec3D::operator/(const float alpha)
{
    if (alpha == 0)
        throw std::string("Division by O");
    else
        return (*this)*(1/alpha);
}
