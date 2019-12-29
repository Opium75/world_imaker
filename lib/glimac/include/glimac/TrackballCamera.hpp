#ifndef __CAMERA_TRACKBALL_HEADER

#define __CAMERA_TRACKBALL_HEADER

#pragma once

#include <iostream>
#include "common.hpp"
#include "glm.hpp"
#include "GenericCamera.hpp"

namespace glimac
{

#define __CAMERA_TRACKBALL_DEFAULT_DISTANCE 5
static const GLfloat DEFAULT_TRACKBALL_ZOOMSPEED = 3;
static const GLfloat DEFAULT_TRACKBALL_XSPEED = 1.;
static const GLfloat DEFAULT_TRACKBALL_YSPEED = 1.;

    class TrackballCamera : public GenericCamera {
    private :
        //coordonnées sphériques
        GLfloat m_fDistance, m_fAngleX, m_fAngleY;
        GLfloat m_zoomSpeed, m_xSpeed, m_ySpeed;


    public :
        TrackballCamera(const GLfloat fDistance = __CAMERA_TRACKBALL_DEFAULT_DISTANCE,
                    const GLfloat fAngleX = __CAMERA_GENERIC_DEFAULT_ANGLE_X,
                    const GLfloat fAngleY = __CAMERA_GENERIC_DEFAULT_ANGLE_Y,
                    const GLfloat zoomSpeed = DEFAULT_TRACKBALL_ZOOMSPEED,
                    const GLfloat xSpeed = DEFAULT_TRACKBALL_XSPEED,
                    const GLfloat ySpeed = DEFAULT_TRACKBALL_YSPEED
        );



        void moveFront(const GLfloat delta);

        void rotateLeft(const GLfloat degrees);

        void rotateUp(const GLfloat degrees);

        glm::mat4 getViewMatrix(void) const override;

        void zoomInput(const GLint input);
        void rotate(const GLfloat x, const GLfloat y);
    };
}

#endif