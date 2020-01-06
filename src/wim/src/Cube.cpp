//
// Created by piptouque on 15/11/2019.
//

#include "../include/wim/Cube.hpp"

#include <utility>
#include <cmath>

namespace wim
{

    inline DisplayPattern Cube::getDisplayPattern() const
    {
        return DisplayPattern::TEXTURED_CUBE;
    }

    Cube::Cube(const Material &material, const SizeInt textureIndex) :
        Displayable(material, textureIndex), Selectable()
    {

    }


    Cube::Cube(const Cube& cube, const XUint x, const YUint floor, const ZUint z) :
        Cube(cube)
    {
        this->position() = Point3Uint(x,floor,z);
    }

    void Cube::swap(Cube& cube)
    {
        std::swap(*this, cube);
    }

    Cube Cube::operator+(const Cube& cube) const
    {
        return Cube(this->material()+cube.material(),
                    std::round((_textureIndex + cube._textureIndex)/2. )
                    );
    }
    Cube& Cube::operator+=(const Cube& cube)
    {
        _material += cube.material();
        _textureIndex = std::round((_textureIndex + cube._textureIndex)/2.);
        return *this;
    }

    Cube& Cube::operator*(const FloatType alpha)
    {
        _material *= alpha;
        return *this;
    }

    Cube& Cube::operator*=(const FloatType alpha)
    {
        _material *= alpha;
        return *this;
    }
/*
    void interpolate(Cube& cube, const Point3Uint& position, const OmegaFunctor<Cube, XUint, FloatType>& rbf)
    {
       rbf(cube, position);

    }
    */

    Cube Cube::Random()
    {
        SizeInt textureIndex;
        textureIndex = RandomScalar<SizeInt>(0, Displayable::getNumberTextures()-1);
        return Cube(Material::Random(),textureIndex);

    }

}