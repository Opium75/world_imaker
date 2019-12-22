//
// Created by piptouque on 19/12/2019.
//

#include "wim/CameraManager.hpp"

namespace wim
{

    const glimac::GenericCamera& CameraManager::getActiveCamera() const
    {
        if ( _activeIndex > _listCamera.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Active index of matrix does not correspond to any camera.");
        else
            return _listCamera.at(_activeIndex);
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

    UniformMatrix CameraManager::getActiveCameraViewMatrix() const
    {
        //Exception thrown by getActiveCamera.
        return this->getActiveCamera().getViewMatrix();
    }

}