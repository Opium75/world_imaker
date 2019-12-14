//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_VEC3D_HPP
#define WORLD_IMAKER_VEC3D_HPP

#pragma once

#include <iostream>
#include <glimac/glm.hpp>

#include "Randomisable.hpp"

namespace wim

{

    class Vec3D //: public RealRandomisable<Vec3D, float>
    {
    public:
        typedef float FloatType;
    protected:
        /* I used a typedef here to somewhat decouple
         * the data structure and its uses in the member methods
         * the type can be accessed outside the class as Vec3D::Coord
         */
        typedef glm::vec3 Coord;
        Coord _coord;
    public:
        Vec3D() = default;
        Vec3D(const FloatType x, const FloatType y, const FloatType z);
        Vec3D(const Vec3D& vec);
        ~Vec3D() = default;

        inline FloatType& x() {return _coord.x;}
        inline FloatType x() const {return _coord.x;}

        inline FloatType& y() {return _coord.y;}
        inline FloatType y() const {return _coord.x;}

        inline FloatType& z() {return _coord.z;}
        inline FloatType z() const {return _coord.z;}

        //No reason to check index bond errors, already done by glm
        inline FloatType& operator[](size_t dim) {return _coord[dim];}
        inline FloatType operator[](size_t dim) const {return _coord[dim];}

        Vec3D& operator=(const Vec3D& vec);
        Vec3D operator+(const Vec3D& vec) const;
        Vec3D& operator+=(const Vec3D& vec);
        ///Returns the symmetric relative to the origin
        inline Vec3D operator-() const { return Vec3D( -_coord );}

        Vec3D& operator*(const FloatType alpha);
        Vec3D& operator/(const FloatType alpha);

        static Vec3D Random(const FloatType lowest=-1, const FloatType highest=1);

        friend std::ostream& operator<<(std::ostream& out, const Vec3D& vec);

    private :
        Vec3D(const Coord& coord);
    };

    inline std::ostream& operator<<(std::ostream& out, const Vec3D& vec) {return out << vec._coord;}

    /* Useful alias for the Vec3D class, conceptually. */
    typedef Vec3D Point3D;
}




#endif //WORLD_IMAKER_VEC3D_HPP
