//
// Created by piptouque on 06/01/2020.
//

#include "../include/wim/Material.hpp"

namespace wim
{
    Material Material::Random()
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

    Material Material::operator+(const Material& material) const
    {
        return Material(colour()+material.colour(),
                        kD()+material.kD(),
                        kS()+material.kS(),
                        shininess()+material.shininess()
                        );
    }
    Material& Material::operator+=(const Material& material)
    {
        colour() += material.colour();
        kD() += material.kD();
        kS() += material.kS();
        shininess() += material.shininess();
        return *this;
    }
    Material& Material::operator*(const FloatType alpha)
    {
        colour() *= alpha;
        kD() *= alpha;
        kS() *= alpha;
        shininess() *= alpha;
        return *this;
    }
    Material& Material::operator*=(const FloatType alpha)
    {
        colour() *= alpha;
        kD() *= alpha;
        kS() *= alpha;
        shininess() *= alpha;
        return *this;
    }
}