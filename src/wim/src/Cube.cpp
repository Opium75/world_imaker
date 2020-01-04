//
// Created by piptouque on 15/11/2019.
//

#include "../include/wim/Cube.hpp"

#include <utility>


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

    Cube Cube::Random()
    {
        SizeInt textureIndex;
        textureIndex = RandomScalar<SizeInt>(0, Displayable::getNumberTextures()-1);
        return Cube(Material::Random(),textureIndex);

    }

}