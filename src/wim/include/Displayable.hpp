//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYABLE_HPP
#define WORLD_IMAKER_DISPLAYABLE_HPP

#pragma once

#include "Vec3D.hpp"

namespace wim
{
    class Displayer;
    ///An interface for elements which will be shown in the world window
    //Is Visited by Displayed
    class Displayable
    {
    protected:
        Point3D anchor;
    public :
        virtual void display(const Displayer& disp) const = 0;
    };



}

#endif //WORLD_IMAKER_DISPLAYABLE_HPP
