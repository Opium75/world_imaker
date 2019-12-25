#ifndef __CAMERA_GENERIC_HEADER

#define __CAMERA_GENERIC_HEADER

#pragma once

#include <iostream>
#include "common.hpp"
#include "glm.hpp"

#define __CAMERA_GENERIC_DEFAULT_ANGLE_X 0
#define __CAMERA_GENERIC_DEFAULT_ANGLE_Y 0

namespace glimac
{

    static const GLfloat DEFAULT_CAMERA_VIEW_WIDTH = 800;
    static const GLfloat DEFAULT_CAMERA_VIEW_HEIGHT = 600;

    static const GLfloat DEFAULT_CAMERA_VIEW_FOVY = 25;

    static const GLfloat DEFAULT_CAMERA_RANGE_NEAR = 0.1f;
    static const GLfloat DEFAULT_CAMERA_RANGE_FAR = 1000.f;

    class GenericCamera {
    private:
        GLfloat _width, _height;
        GLfloat _fov;
        GLfloat _rangeNear, _rangeFar;


    public :
        GenericCamera(const GLfloat width=DEFAULT_CAMERA_VIEW_WIDTH,
                const GLfloat height=DEFAULT_CAMERA_VIEW_HEIGHT,
                const GLfloat fov=DEFAULT_CAMERA_VIEW_FOVY,
                const GLfloat rangeNear=DEFAULT_CAMERA_RANGE_NEAR,
                const GLfloat rangeFar=DEFAULT_CAMERA_RANGE_FAR) :
                    _width(width), _height(height), _fov(fov), _rangeNear(rangeNear), _rangeFar(rangeFar)
        {}

        virtual glm::mat4 getViewMatrix() const = 0;

        inline glm::mat4 getProjectionMatrix() const
        {
            return glm::perspective(
                    _fov,
                    _width/_height,
                    _rangeNear,
                    _rangeFar
                    );
        }
    };

}

#endif