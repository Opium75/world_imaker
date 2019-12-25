//
// Created by piptouque on 19/12/2019.
//

#include "wim/CameraManager.hpp"

namespace wim
{


    const Camera& CameraManager::camera(const SizeInt index) const
    {
        if ( index > _listCamera.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Index of matrix does not correspond to any camera.");
        else
            return _listCamera.at(index);
    }

    Camera& CameraManager::camera(const SizeInt index)
    {
        if ( index > _listCamera.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Index of matrix does not correspond to any camera.");
        else
            return _listCamera.at(index);
    }

    const Camera& CameraManager::active() const
    {
      return this->camera(_activeIndex);
    }

    Camera& CameraManager::active()
    {
        return this->camera(_activeIndex);
    }

    void CameraManager::setActiveCamera(SizeInt index) {
        if (index > _listCamera.size())
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, " Trying to set a non-existent camera as active.");
        else
            _activeIndex = index;
    }

    void CameraManager::setActiveCameraNext()
    {
        if (_listCamera.begin() + _activeIndex >= _listCamera.end() )
            _activeIndex = 0;
        else
            ++_activeIndex;
    }

    void CameraManager::deleteCamera(SizeInt index)
    {
        if( index > _listCamera.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Trying to delete a non-existent camera.");
        else
            _listCamera.erase(_listCamera.begin()+index);
    }

    UniformMatrix CameraManager::getCameraViewMatrix(const SizeInt index) const
    {
        try
        {
            return this->camera(index).getViewMatrix();
        }
        catch(Exception& e)
        {
            throw;
        }
    }

    UniformMatrix CameraManager::getProjectionMatrix(const wim::SizeInt index) const
    {
        return this->camera(index).getProjectionMatrix();
    }

    UniformMatrix CameraManager::getElementModelViewMatrix(const SizeInt index, const Renderable& item) const
    {
        UniformMatrix MVMatrix = getCameraViewMatrix(index);
        /* matching rotation around origin of World .
        * -> nothing to do
         */;
        //Position
        MVMatrix = glm::translate(
                MVMatrix,
                item.getAnchor().getCoord()
        );

        //Scale
        /* nothing to do ?
         *
        MVMatrix = glm::scale(MVMatrix,
                ???
                );
        */

        /* Self rotation
         * nothing to do.
         */
        return MVMatrix;
    }

}