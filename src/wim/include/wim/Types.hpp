//
// Created by piptouque on 21/12/2019.
//

#ifndef WORLD_IMAKER_TYPES_HPP
#define WORLD_IMAKER_TYPES_HPP

#pragma once

#include <cstddef>

#define GLM_FORCE_RADIANS
#include <glimac/glm.hpp>



namespace wim
{
    typedef float FloatType;

    typedef std::uint32_t XUint, YUint, ZUint;
    typedef std::int32_t XInt, YInt, ZInt;
    typedef std::size_t SizeInt;


    typedef glm::mat4 UniformMatrix;

}

#endif //WORLD_IMAKER_TYPES_HPP
