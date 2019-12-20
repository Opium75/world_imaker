#ifndef __CAMERA_FREEFLY_HEADER

#define __CAMERA_FREEFLY_HEADER

#pragma once


#include <iostream>
#include "common.hpp"
#include "glm.hpp"
#include "GenericCamera.hpp"

namespace glimac
{

#define __WHATISTHIS_PI glm::pi<float>()

#define __CAMERA_FREEFLY_DEFAULT_POSITION (glm::vec3(0.f, 0.f, 0.5f))
#define __CAMERA_FREEFLY_DEFAULT_PHI __WHATISTHIS_PI
#define __CAMERA_FREEFLY_DEFAULT_THETA 0

    class FreeflyCamera : public GenericCamera {
    private :
        //coordonnées sphériques
        glm::vec3 m_Position;
        float m_fPhi, m_fTheta; //RADIANS
        //variables redondantes
        glm::vec3 m_FrontVector, m_LeftVector, m_UpVector;
    public :
        FreeflyCamera(const glm::vec3 Position = __CAMERA_FREEFLY_DEFAULT_POSITION,
                      const float fPhi = __CAMERA_FREEFLY_DEFAULT_PHI,
                      const float fTheta = __CAMERA_FREEFLY_DEFAULT_THETA
        );

        void moveLeft(const float t);

        void moveFront(const float t);

        void rotateLeft(const float degrees);

        void rotateUp(const float degrees);

        glm::mat4 getViewMatrix(void) const override;

    private :
        void computeDirectionVector(void);
    };

}
#endif