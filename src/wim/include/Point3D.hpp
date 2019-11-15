//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_POINT3D_HPP
#define WORLD_IMAKER_POINT3D_HPP

#pragma once

#include <iostream>
#include <glimac/glm.hpp>

namespace wim
{
    class Point3D
    {
    private:
        glm::vec3 _coord;
    public:
        Point3D() = default;
        Point3D(const float x, const float y, const float z);
        Point3D(const Point3D& p);
        ~Point3D() = default;

        inline float& x() {return _coord.x;}
        inline float x() const {return _coord.x;}

        inline float& y() {return _coord.y;}
        inline float y() const {return _coord.x;}

        inline float& z() {return _coord.z;}
        inline float z() const {return _coord.z;}

        //No point checking index bond errors, already done by glm
        inline float& operator[](size_t dim) {return _coord[dim];}
        inline float operator[](size_t dim) const {return _coord[dim];}

        Point3D& operator=(const Point3D& p);
        Point3D operator+(const Point3D& p) const;
        Point3D& operator+=(const Point3D& p);
        ///Returns the symmetric of the point relative to the origin
        inline Point3D operator-() const { return Point3D( -_coord );}

        Point3D& operator*(const float alpha);
        Point3D& operator/(const float alpha);

        friend std::ostream& operator<<(std::ostream& out, const Point3D& p);

    private :
        Point3D(const glm::vec3& coord);
    };

    inline std::ostream& operator<<(std::ostream& out, const Point3D& p) {return out << p._coord;}
}

#endif //WORLD_IMAKER_POINT3D_HPP
