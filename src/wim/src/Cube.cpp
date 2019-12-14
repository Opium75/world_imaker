//
// Created by piptouque on 15/11/2019.
//

#include "../include/wim/Cube.hpp"

namespace wim
{

    Cube::Cube(const Colour &colour) : _colour(colour)
    {

    }

    Cube::Cube(const Cube &cube) : Cube(cube._colour)
    {

    }

    Cube& Cube::operator=(const Cube& cube)
    {
        _colour = cube._colour;
        return *this;
    }

    Cube Cube::Random()
    {
        return Cube(Colour::Random());
    }

}