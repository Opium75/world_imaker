#ifndef __CAMERA_GENERIC_HEADER

#define __CAMERA_GENERIC_HEADER

#pragma once

#include <iostream>
#include "common.hpp"
#include "glm.hpp"

#define __CAMERA_GENERIC_DEFAULT_ANGLE_X 0
#define __CAMERA_GENERIC_DEFAULT_ANGLE_Y 0



class GenericCamera {
	public :
		GenericCamera();
		virtual glm::mat4 getViewMatrix(void) const;
};


#endif