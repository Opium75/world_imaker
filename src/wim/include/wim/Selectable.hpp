//
// Created by piptouque on 29/12/2019.
//

#ifndef WORLD_IMAKER_SELECTABLE_HPP
#define WORLD_IMAKER_SELECTABLE_HPP

#pragma once

#include <memory>

namespace wim
{
    class Selectable
    {

    };

    typedef std::unique_ptr<Selectable> SelectablePtr;
}

#endif //WORLD_IMAKER_SELECTABLE_HPP
