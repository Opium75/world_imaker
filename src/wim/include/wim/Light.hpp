//
// Created by piptouque on 18/12/2019.
//

#ifndef WORLD_IMAKER_LIGHT_HPP
#define WORLD_IMAKER_LIGHT_HPP

#include <GL/gl.h>
#include "Vec3D.hpp"

#pragma once

namespace wim {


    class AbstractLight {
    private:
        GLfloat _intensity;

    public:
        AbstractLight();
        virtual ~AbstractLight() = 0;
    };

    class PointLight : public AbstractLight {

    private:
        Point3D _origin; //coordinates of the light in World.
    public:
        ~PointLight() override = default;
    };

    class DirectionalLight : public AbstractLight {

    private:
        Vec3D _direction;
    public:
        ~DirectionalLight() override = default;
    };

}

#endif //WORLD_IMAKER_LIGHT_HPP
