//
// Created by piptouque on 19/12/2019.
//

#include "wim/CameraManager.hpp"

namespace wim
{

    const glimac::GenericCamera& CameraManager::getCurrentCamera() const
    {
        if ( _currentIndex > _listCamera.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Current index of matrix does not correspond to any camera.");
        else
            return _listCamera.at(_currentIndex);
    }

    void CameraManager::setCurrentCamera(SizeInt index) {
        if (index > _listCamera.size())
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, " Trying to set a non-existent camera as current.");
        else
            _currentIndex = index;
    }

    void CameraManager::setCurrentCameraNext()
    {
        if (_listCamera.begin() + _currentIndex >= _listCamera.end() )
            _currentIndex = 0;
        else
            ++_currentIndex;
    }

    void CameraManager::deleteCamera(SizeInt index)
    {
        if( index > _listCamera.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Trying to delete a non-existent camera.");
        else
            _listCamera.erase(_listCamera.begin()+index);
    }

    glm::mat4 CameraManager::getCurrentCameraViewMatrix() const
    {
        //Exception thrown by getCurrentCamera.
        return this->getCurrentCamera().getViewMatrix();
    }

}