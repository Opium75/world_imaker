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

#include "Displayable.hpp"

#include "Exception.hpp"
#include "Types.hpp"


namespace wim
{
    typedef glimac::TrackballCamera Camera;
    class CameraManager
    {
    public:
        typedef std::deque<Camera> ListCamera;
    private:
        ListCamera _listCamera;
        SizeInt _activeIndex;
    public:
        CameraManager()
        {
            this->addTrackball();
            _activeIndex = 0;
        };
        ~CameraManager() = default;

        inline void addTrackball() { _listCamera.push_back(glimac::TrackballCamera());}
        inline void addFreefly() {_listCamera.push_back(glimac::TrackballCamera());}

        const Camera& camera(const SizeInt index) const;
        Camera& camera(const SizeInt index);

        const Camera& active() const;
        Camera& active();
        void setActiveCamera(SizeInt index);
        ///brief: Set active camera as the next one in the list. It was the last one, it loops back to the first.
        void setActiveCameraNext();

        void deleteCamera(SizeInt index);


        UniformMatrix getCameraViewMatrix(const SizeInt index) const;
        UniformMatrix getActiveCameraViewMatrix() const;

        UniformMatrix getElementModelViewMatrix(const SizeInt index, const Renderable& item) const;

        inline UniformMatrix getActiveElementModelViewMatrix(const Renderable& item) const
        {
            return this->getElementModelViewMatrix(_activeIndex, item);
        }

        inline UniformMatrix getActiveProjectionMatrix() const
        {
            return this->active().getProjectionMatrix();
        }

        inline void zoom(const SizeInt index, const GLint input)
        {
            this->camera(index).zoomInput(input);
        }

        inline void rotate(const SizeInt index, const GLfloat x, const GLfloat y)
        {
            this->camera(index).rotateXY(x,y);
        }

        inline void rotateActive(const GLfloat x, const GLfloat y)
        {
            this->active().rotateXY(x,y);
        }

        inline void zoomActive(const GLint input)
        {
            this->zoom(_activeIndex, input);
        }
    };

    //Cameras will be shared between the Model and the Scene Renderer.
    typedef std::shared_ptr<CameraManager> CameraManagerPtr;
}


#endif //WORLD_IMAKER_CAMERAMANAGER_HPP
