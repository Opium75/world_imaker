//
// Created by piptouque on 15/11/2019.
//

#include "../include/Cube.hpp"

using namespace wim;

Cube::Cube(const Colour& colour) : _colour(colour)
{

}

Cube::Cube(const Cube& cube) : _colour(cube._colour)
{

}

Cube Cube::Random()
{
    return Cube(Colour::Random());
}