//
// Created by piptouque on 19/12/2019.
//

#ifndef WORLD_IMAKER_CAMERAMANAGER_HPP
#define WORLD_IMAKER_CAMERAMANAGER_HPP

#pragma once

#include <deque>

#include <glm/glm.hpp>

#include <glimac/GenericCamera.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include "Exception.hpp"


namespace wim
{
    class CameraManager
    {
    public:
        typedef std::size_t SizeInt;
        typedef std::deque<glimac::TrackballCamera> ListCamera;
    private:
        ListCamera _listCamera;
        SizeInt _currentIndex;
    public:
        CameraManager() = default;
        ~CameraManager() = default;

        inline void addTrackball() { _listCamera.push_back(glimac::TrackballCamera());}
        inline void addFreefly() {_listCamera.push_back(glimac::TrackballCamera());}

        const glimac::GenericCamera& getCurrentCamera() const;
        void setCurrentCamera(SizeInt index);
        ///brief: Set current camera as the next one in the list. It was the last one, it loops back to the first.
        void setCurrentCameraNext();

        void deleteCamera(SizeInt index);

        glm::mat4 getCurrentCameraViewMatrix() const;


    };

}


#endif //WORLD_IMAKER_CAMERAMANAGER_HPP
