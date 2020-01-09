//
// Created by piptouque on 19/11/2019.
//

#ifndef WORLD_IMAKER_VEC3D_HPP
#define WORLD_IMAKER_VEC3D_HPP

#pragma once

#include <type_traits>
#include <iostream>

#include "Types.hpp"
#include "Exception.hpp"
#include "Randomisable.hpp"

#include <glm/ext.hpp>

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
        typedef glm::detail::tvec3<T, glm::highp> Coord;
        Coord _coord;
    public:
        /* CONSTRUCTORS */
        TVec3D() = default;
        TVec3D(const Coord& coord) : _coord(coord) {};
        TVec3D(const T x, const T y, const T z) : _coord(x,y,z)
        {
            //Constraining use of class to arithmetic types.
            static_assert(std::is_arithmetic<T>::value, "Vec3D used for arithmetics with float or int types.");
        };
        constexpr TVec3D(const T list[3]) : _coord(list[0], list[1], list[2]) {}
        TVec3D(const TVec3D& vec) = default;
        //Casting one type to the other
        template<typename U>
        TVec3D(const TVec3D<U>& vec) : _coord(static_cast<Coord>(vec._coord)) {}
        /* */
        ~TVec3D() = default;

        inline T& x() {return _coord.x;}
        inline T x() const {return _coord.x;}

        inline T& y() {return _coord.y;}
        inline T y() const {return _coord.y;}

        inline T& z() {return _coord.z;}
        inline T z() const {return _coord.z;}

       const Coord& getCoord() const { return _coord;}

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

        /** NOTE : the following two functions will not cast unsigned types to signed
         * So they do not work with Point3Uint
         */
        ///Returns the symmetric relative to the origin
        TVec3D operator-() const
        {
            static_assert(!std::is_signed<T>::value);
            return TVec3D( -_coord );
        }

        TVec3D operator-(const TVec3D& vec) const
        {
            static_assert(!std::is_signed<T>::value);
            return TVec3D(this->_coord - vec._coord);
        }
        /** **/

        TVec3D& operator*(const T alpha)
        {
            for (int i = 0; i < _coord.length(); ++i)
                _coord[i] *= alpha;
            return *this;
        }
        TVec3D& operator*=(const T alpha)
        {
            this->operator*(alpha);
            return *this;
        }

        TVec3D& operator/(const T alpha)
        {
            if (alpha == static_cast<T>(0))
                throw Exception(ExceptCode::DOMAIN_ERROR, 1, "Trying to divide by O.");
            else
                return (*this) * (1 / alpha);
        }

        template<typename D=T, SizeInt n=2>
        D norm() const
        {
            D l = static_cast<D>(n);
            return std::pow(
                    std::pow(static_cast<D>(std::abs(x())),l) +
                    std::pow(static_cast<D>(std::abs(y())),l) +
                    std::pow(static_cast<D>(std::abs(z())), l),
                    1/l
                    );
        }

        /** NOTE : distnace can be used by using type **/
        template<typename D=T, SizeInt n=2>
        D distance(const TVec3D vec) const
        {
            TVec3D<D> diff;
            diff.x() = static_cast<D>(x()) - static_cast<D>(vec.x());
            diff.y() = static_cast<D>(y()) - static_cast<D>(vec.y());
            diff.z() = static_cast<D>(z()) - static_cast<D>(vec.z());
            return diff.template norm<D, n>();
        }

        static TVec3D Random(const T lowest= static_cast<T>(-1), const T highest= static_cast<T>(1))
        {
            T x, y, z;
            x = RandomScalar(lowest, highest);
            y = RandomScalar(lowest, highest);
            z = RandomScalar(lowest, highest);
            return TVec3D(x, y, z);
        }

        std::string toString() const {return glm::to_string(_coord);}
        friend inline std::ostream& operator<<(std::ostream& out, const TVec3D<T>& vec) {return out << vec._coord;}
    };


    /* Useful alias for the Vec3D class, conceptually. */
    template<typename T>
    using TPoint3D = TVec3D<T>;

    using Vec3D = TVec3D<FloatType>;
    using Point3D = Vec3D;

    using Vec3Uint = TVec3D<XUint>;
    using Point3Uint = Vec3Uint;

}




#endif //WORLD_IMAKER_VEC3D_HPP
