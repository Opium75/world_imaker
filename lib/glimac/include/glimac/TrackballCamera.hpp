#ifndef __CAMERA_TRACKBALL_HEADER

#define __CAMERA_TRACKBALL_HEADER

#pragma once

#include <iostream>
#include "common.hpp"
#include "glm.hpp"
#include "GenericCamera.hpp"


#define __CAMERA_TRACKBALL_DEFAULT_DISTANCE 5


class TrackCamera {
	private :
		//coordonnées sphériques
		float m_fDistance, m_fAngleX, m_fAngleY;
	public :
		TrackCamera(const float fDistance =__CAMERA_TRACKBALL_DEFAULT_DISTANCE,
					const float fAngleX = __CAMERA_GENERIC_DEFAULT_ANGLE_X, 
					const float fAngleY = __CAMERA_GENERIC_DEFAULT_ANGLE_Y
					);
		void moveFront(const float delta);
		void rotateLeft(const float degrees);
		void rotateUp(const float degrees);
		glm::mat4 getViewMatrix(void) const;
};


#endif