//
// Created by piptouque on 19/12/2019.
//

#ifndef WORLD_IMAKER_CAMERAMANAGER_HPP
#define WORLD_IMAKER_CAMERAMANAGER_HPP

#pragma once

#include <memory>
#include <deque>

#include <glm/glm.hpp>

#include <glimac/GenericCamera.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>
#include "Exception.hpp"
#include "Types.hpp"


namespace wim
{
    class CameraManager
    {
    public:
        typedef std::deque<glimac::TrackballCamera> ListCamera;
    private:
        ListCamera _listCamera;
        SizeInt _activeIndex;
    public:
        CameraManager() = default;
        ~CameraManager() = default;

        inline void addTrackball() { _listCamera.push_back(glimac::TrackballCamera());}
        inline void addFreefly() {_listCamera.push_back(glimac::TrackballCamera());}

        const glimac::GenericCamera& getActiveCamera() const;
        void setActiveCamera(SizeInt index);
        ///brief: Set active camera as the next one in the list. It was the last one, it loops back to the first.
        void setActiveCameraNext();

        void deleteCamera(SizeInt index);

        UniformMatrix getActiveCameraViewMatrix() const;
    };

    //Cameras will be shared between the Model and the Scene Renderer.
    typedef std::shared_ptr<CameraManager> CameraManagerPtr;
}


#endif //WORLD_IMAKER_CAMERAMANAGER_HPP
