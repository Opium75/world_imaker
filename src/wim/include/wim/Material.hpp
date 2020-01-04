//
// Created by piptouque on 23/12/2019.
//

#ifndef WORLD_IMAKER_MATERIAL_HPP
#define WORLD_IMAKER_MATERIAL_HPP

#pragma once

#include <iostream>
#include <utility>

#include "Types.hpp"
#include "Vec3D.hpp"
#include "Colour.hpp"

#include "Randomisable.hpp"

namespace wim
{
    class Material
    {
    private:
      Colour _colour;
      Vec3D _kD, _kS;
      FloatType _shininess;
    public:
        Material() = default;
        Material(const Colour& colour) : _colour(colour) {}
        Material(const Colour& colour, const Vec3D& kD, const Vec3D& kS, const FloatType shininess) :
            _colour(colour), _kD(kD), _kS(kS), _shininess(shininess)
        {

        }
        Material(const Material& material) = default;
        ~Material() = default;

        Material& operator=(const Material& material) = default;

        inline const Colour& colour() const {return _colour;}
        inline Colour& colour() {return _colour;}

        inline const Vec3D& kD() const {return _kD;}
        inline Vec3D& kD() {return _kD;}

        inline const Vec3D& kS() const {return _kS;}
        inline Vec3D& kS() {return _kS;}

        inline FloatType shininess() const {return _shininess;}
        inline FloatType& shininess() {return _shininess;}

        static Material Random()
        {
            //Everything between 0 and 1!!!
            /* I swear I spent two whole days doing nothing productive
             * because I would keep the Ks and Kd COEFFS higher than 1.
             * Of course the lighting would be weird THESE ARE COEFFICENTS!
             */
            return Material(Colour::Random(),
                    Vec3D::Random(0,1),
                    Vec3D::Random(0,1),
                    RandomScalar<FloatType >(0,128)
            );
        }

        friend std::ostream& operator<<(std::ostream& out, const Material& material)
        {
            out << material._colour << " | " << material._kD << ", " << material._kS << " | " << material._shininess;
            return out;
        }
    };
}


#endif //WORLD_IMAKER_MATERIAL_HPP
