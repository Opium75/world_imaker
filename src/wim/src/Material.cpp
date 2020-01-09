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
        return this->average(material);
    }
    Material& Material::operator+=(const Material& material)
    {
        *this = this->average(material);
        return *this;
    }

    Material  Material::average(const Material& material) const
    {
        Material avg;
        avg.colour() = colour().average(material.colour());
        avg.kD()  = (kD() + material.kD())/2.;
        avg.kS() = (kS() + material.kS())/2.;
        avg.shininess() = (shininess() + material.shininess())/2.;
        return avg;
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