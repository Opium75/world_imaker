//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_VEC3D_HPP
#define WORLD_IMAKER_VEC3D_HPP

#pragma once

#include <iostream>
#include <glimac/glm.hpp>

namespace wim

{

    class Vec3D
    {
    protected:
        /* I used a typedef here to somewhat decouple
         * the data structure and its uses in the member methods
         * the type can be accessed outside the class as Vec3D::Coord
         */
        typedef glm::vec3 Coord;
        Coord _coord;
    public:
        Vec3D() = default;
        Vec3D(const float x, const float y, const float z);
        Vec3D(const Vec3D& vec);
        ~Vec3D() = default;

        inline float& x() {return _coord.x;}
        inline float x() const {return _coord.x;}

        inline float& y() {return _coord.y;}
        inline float y() const {return _coord.x;}

        inline float& z() {return _coord.z;}
        inline float z() const {return _coord.z;}

        //No reason to check index bond errors, already done by glm
        inline float& operator[](size_t dim) {return _coord[dim];}
        inline float operator[](size_t dim) const {return _coord[dim];}

        Vec3D& operator=(const Vec3D& vec);
        Vec3D operator+(const Vec3D& vec) const;
        Vec3D& operator+=(const Vec3D& vec);
        ///Returns the symmetric relative to the origin
        inline Vec3D operator-() const { return Vec3D( -_coord );}

        Vec3D& operator*(const float alpha);
        Vec3D& operator/(const float alpha);

        friend std::ostream& operator<<(std::ostream& out, const Vec3D& vec);

    private :
        Vec3D(const Coord& coord);
    };

    inline std::ostream& operator<<(std::ostream& out, const Vec3D& vec) {return out << vec._coord;}

    /* Useful alias for the Vec3D class, conceptually. */
    typedef Vec3D Point3D;
}




#endif //WORLD_IMAKER_VEC3D_HPP
