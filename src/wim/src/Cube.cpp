//
// Created by piptouque on 15/11/2019.
//

#include "../include/wim/Cube.hpp"

namespace wim
{

    Cube::Cube(const Material &material) : Displayable(material)
    {

    }

    Cube& Cube::operator=(Cube cube)
            {
        std::swap(*this, cube);
        return *this;
    }

    Cube Cube::Random()
    {
        return Cube(Material::Random());

    }

}