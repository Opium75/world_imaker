//
// Created by piptouque on 29/12/2019.
//

#include "wim/Cursor.hpp"

#include <algorithm>

namespace wim
{
    void Cursor::setX(const XUint x)
    {
        _position.x() = std::min(x, this->getWorldWidth()-1);
    }
    void Cursor::setY(const YUint y)
    {
        /* NOT CHECKING Y-AXIS, SINCE IT IS DYNAMIC.*/
        _position.y() = y;
    }
    void Cursor::setZ(const ZUint z)
    {
        _position.z() = std::min(z, this->getWorldLength()-1);
    }

    void Cursor::moveX(const Xint delta)
    {
        Xint x =  std::max<Xint>(0, (Xint)_position.x()+delta);
        this->setX(x);
    }
    void Cursor::moveY(const Yint delta)
    {
        Xint y =  std::max<Yint>(0, (Yint)_position.y()+delta);
        this->setY(y);
    }
    void Cursor::moveZ(const Zint delta)
    {
        Xint z =  std::max<Zint>(0, (Zint)_position.z()+delta);
        this->setZ(z);
    }

    void Cursor::setPosition(const XUint x, const YUint y, const ZUint z)
    {
        setX(x); setY(y); setZ(z);
    }

    const Point3Int& Cursor::getPosition() const
    {
        return _position;
    }
}
