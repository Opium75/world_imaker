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
        CameraManager() : _activeIndex(0)
        {
            this->addTrackball();
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




    private:
        UniformMatrix getCameraViewMatrix(const SizeInt index) const;
        inline UniformMatrix getActiveCameraViewMatrix() const {return this->getCameraViewMatrix(_activeIndex);}
        UniformMatrix getElementModelViewMatrix(const SizeInt index, const Renderable& item) const;
        inline UniformMatrix getActiveElementModelViewMatrix(const Renderable& item) const{return this->getElementModelViewMatrix(_activeIndex, item);}

        UniformMatrix getProjectionMatrix(const SizeInt index) const;
        inline UniformMatrix getActiveProjectionMatrix() const{return this->getProjectionMatrix(_activeIndex);}
        inline void zoom(const SizeInt index, const GLint input) {this->camera(index).zoomInput(input);}
        inline void rotate(const SizeInt index, const GLfloat xDeg, GLfloat yDeg) {this->camera(index).rotate(xDeg,yDeg);}

        inline void zoomActive(const GLint input){this->zoom(_activeIndex, input);}
        inline void rotateActive(const GLfloat xDeg, const GLfloat yDeg){this->active().rotate(xDeg,yDeg);}

    public:
        inline UniformMatrix getCameraViewMatrix() const
        {
            return this->getActiveCameraViewMatrix();
        }

        inline UniformMatrix getProjectionMatrix() const
        {
            return this->getActiveProjectionMatrix();
        }

        inline UniformMatrix getElementModelViewMatrix(const Renderable& item) const
        {
            return this->getActiveElementModelViewMatrix(item);
        }

        inline void rotate(const GLfloat xDeg, const GLfloat yDeg)
        {
            this->rotateActive(xDeg, yDeg);
        }
        inline void zoom(const GLint input)
        {
            this->zoomActive(input);
        }
    };

    //Cameras will be shared between the Model and the Scene Renderer.
    typedef std::unique_ptr<CameraManager> CameraManagerPtr;
}


#endif //WORLD_IMAKER_CAMERAMANAGER_HPP
