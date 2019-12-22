//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_VEC3D_HPP
#define WORLD_IMAKER_VEC3D_HPP

#pragma once

#include <type_traits>
#include <iostream>
#include <glimac/glm.hpp>

#include "Types.hpp"
#include "Exception.hpp"
#include "Randomisable.hpp"

namespace wim

{

    template<typename T>
    class TVec3D
    {
    public:
        template<typename U>
        friend class TVec3D;
    protected:
        /* I used a typedef here to somewhat decouple
         * the data structure and its uses in the member methods
         * the type can be accessed outside the class as Vec3D::Coord
         */
        typedef glm::detail::tvec3<T, glm::mediump> Coord;
        Coord _coord;
    private :
        TVec3D(const Coord& coord) : _coord(coord) {};
    public:
        TVec3D() = default;
        TVec3D(const T x, const T y, const T z) : _coord(x,y,z)
        {
            //Constraining use of class
            static_assert(std::is_arithmetic<T>::value, "Vec3D used for arithmetics with float or int types.");
        };
        TVec3D(const TVec3D& vec) = default;
        //Casting one type to the other
        template<typename U>
        TVec3D(const TVec3D<U>& vec) : _coord(static_cast<Coord>(vec._coord))
        {

        }
        ~TVec3D() = default;

        inline T& x() {return _coord.x;}
        inline T x() const {return _coord.x;}

        inline T& y() {return _coord.y;}
        inline T y() const {return _coord.x;}

        inline T& z() {return _coord.z;}
        inline T z() const {return _coord.z;}

        //No reason to check index bond errors, already done by glm
        inline T& operator[](size_t dim) {return _coord[dim];}
        inline T operator[](size_t dim) const {return _coord[dim];}

        //I just learnt of the copy and swap idiom, so here goes:
        TVec3D& operator=(TVec3D vec)
        {
            std::swap(_coord, vec._coord);
            return *this;
        }
        TVec3D operator+(const TVec3D& vec) const
        {
            return TVec3D(this->_coord + vec._coord);
        }
        TVec3D& operator+=(const TVec3D& vec)
        {
            this->_coord += vec._coord;
            return *this;
        };
        ///Returns the symmetric relative to the origin
        inline TVec3D operator-() const { return TVec3D( -_coord );}

        TVec3D& operator*(const T alpha)
        {
            for (int i = 0; i < _coord.length(); ++i)
                _coord[i] *= alpha;
            return *this;
        }
        TVec3D& operator/(const T alpha)
        {
            if (alpha == static_cast<T>(0))
                throw Exception(ExceptCode::DOMAIN_ERROR, 1, "Trying to divide by O.");
            else
                return (*this) * (1 / alpha);
        }

        static TVec3D Random(const T lowest= static_cast<T>(-1), const T highest= static_cast<T>(1))
        {
            T x, y, z;
            if constexpr ( std::is_floating_point<T>::value )
            {
                x = RealRandomisable<TVec3D, T>::Random(lowest, highest);
                y = RealRandomisable<TVec3D, T>::Random(lowest, highest);
                z = RealRandomisable<TVec3D, T>::Random(lowest, highest);
            }
            else
            {
                //Int type
                x = IntRandomisable<TVec3D, T>::Random(lowest, highest);
                y = IntRandomisable<TVec3D, T>::Random(lowest, highest);
                z = IntRandomisable<TVec3D, T>::Random(lowest, highest);
            }
            return TVec3D(x, y, z);
        }

        friend inline std::ostream& operator<<(std::ostream& out, const TVec3D<T>& vec) {return out << vec._coord;}

    };


    /* Useful alias for the Vec3D class, conceptually. */
    template<typename T>
    using TPoint3D = TVec3D<T>;

    using Vec3D = TVec3D<FloatType>;
    using Point3D = Vec3D;

    using Vec3Int = TVec3D<XUint>;
    using Point3Int = Vec3Int;

}




#endif //WORLD_IMAKER_VEC3D_HPP
