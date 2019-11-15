//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYABLE_HPP
#define WORLD_IMAKER_DISPLAYABLE_HPP

#pragma once

#include "Point3D.hpp"

namespace wim
{
    ///An interface for elements which will be shown in the world window
    //Perhaps a Visitor class would be better ?
    class Displayable
    {
    protected:
        Point3D anchor;
    public :
        virtual void display() const = 0;
    };

}

#endif //WORLD_IMAKER_DISPLAYABLE_HPP
