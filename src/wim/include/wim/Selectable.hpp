//
// Created by piptouque on 29/12/2019.
//

#ifndef WORLD_IMAKER_SELECTABLE_HPP
#define WORLD_IMAKER_SELECTABLE_HPP

#pragma once

#include <deque>

#include "Types.hpp"

namespace wim
{
    class Selectable
    {
        Point3Uint _position;
    public:
        Selectable() = default;
        Selectable(const Point3Uint& position) : _position(position) {}
        ~Selectable() = default;

        inline const Point3Uint& position() const {return _position;}
        inline Point3Uint& position() {return _position;}

        inline XUint x() const {return _position.x();}
        inline XUint x() {return _position.x();}
        inline YUint y() const {return _position.y();}
        inline YUint y() {return _position.y();}
        inline ZUint z() const {return _position.z();}
        inline ZUint z() {return _position.z();}
    };


}

#endif //WORLD_IMAKER_SELECTABLE_HPP
