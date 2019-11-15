//
// Created by piptouque on 15/11/2019.
//

#include "../include/Point3D.hpp"

using namespace wim;

Point3D::Point3D(const float x, const float y, const float z) :
    _coord(x,y,z)
{

}

Point3D::Point3D(const Point3D& p) : _coord(p._coord)
{

}

Point3D::Point3D(const glm::vec3 &coord) : _coord(coord)
{

}

Point3D& Point3D::operator=(const Point3D& p)
{
    this->_coord = p._coord;
    return *this;
}

Point3D Point3D::operator+(const Point3D& p) const
{
    return Point3D( this->_coord + p._coord );
}

Point3D& Point3D::operator+=(const Point3D& p)
{
    this->_coord += p._coord;
    return *this;
}

Point3D& Point3D::operator*(const float alpha)
{
    for (int i = 0; i < _coord.length(); ++i)
        _coord[i] *= alpha;
    return *this;
}

Point3D& Point3D::operator/(const float alpha)
{
    if (alpha == 0)
        throw std::string("Division by O");
    else
        return (*this)*(1/alpha);
}
