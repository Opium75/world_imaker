//
// Created by piptouque on 25/11/2019.
//

//Already includes Cube, CubeStack, CubeWorld headers.
#include "../include/Displayer.hpp"

using namespace wim;

void Cube::display(const Displayer& disp) const
{
    return disp.display(*this);
}

void CubeStack::display(const Displayer& disp) const
{
    return disp.display(*this);
}

void CubeWorld::display(const Displayer& disp) const
{
    return disp.display(*this);
}

void Displayer::display(const Cube &cube) const
{
    std::cout << cube << std::endl;
}

void Displayer::display(const CubeStack &stack) const
{
    std::cout << stack << std::endl;
}

void Displayer::display(const CubeWorld &world) const
{
    std::cout << world(0,0) << std::endl;
}
