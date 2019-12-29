//
// Created by piptouque on 15/11/2019.
//

#include "../include/wim/Cube.hpp"

namespace wim
{

    Cube::Cube(const Material &material, const SizeInt textureIndex) : Displayable(material, textureIndex)
    {

    }

    Cube& Cube::operator=(Cube cube)
            {
        std::swap(*this, cube);
        return *this;
    }

    Cube Cube::Random()
    {
        SizeInt textureIndex;
        textureIndex = RandomScalar<SizeInt>(0, Displayable::getNumberTextures()-1);
        return Cube(Material::Random(),textureIndex);

    }

}