//
// Created by piptouque on 23/12/2019.
//

#include "../include/wim/Light.hpp"

namespace wim
{

    void LightManager::addPoint(const PointLight& pLight)
    {
        if( _listPoint.size() >= MAX_NB_EACH_LIGHT )
            throw Exception(ExceptCode::OVERFLOW, 1, "Maximum number of point lights reached." );
        _listPoint.push_back(pLight);
        this->notify();
    }
    void LightManager::addDir(const DirectionalLight& dLight)
    {
        if( _listDirectional.size() >= MAX_NB_EACH_LIGHT )
            throw Exception(ExceptCode::OVERFLOW, 1, "Maximum number of directional lights reached." );
        _listDirectional.push_back(dLight);
        this->notify();
    }
    void LightManager::removePoint(const size_t index)
    {
        if( index >= _listPoint.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Point light at index does not exist." );
        _listPoint.erase(_listPoint.begin()+index);
        this->notify();
    }
    void LightManager::removeDir(const size_t index)
    {
        if( index >= _listDirectional.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Directional light at index does not exist." );
        _listDirectional.erase(_listDirectional.begin()+index);
        this->notify();
    }

    AmbiantLight AmbiantLight::Random()
    {
        return AmbiantLight(Colour::Random());
    }

    PointLight PointLight::Random()
    {
        return PointLight(AmbiantLight::Random(),
                                Vec3D::Random()
        );
    }

    DirectionalLight DirectionalLight::Random()
    {
        return DirectionalLight(AmbiantLight::Random(),
                Vec3D::Random()
                );
    }
    LightManager::LightManager() :
        _listPoint(), _listDirectional(), _ambiant()
    {
        //Enough space for lights
        _listPoint.reserve(MAX_NB_EACH_LIGHT);
        _listDirectional.reserve(MAX_NB_EACH_LIGHT);
        /* */
    };

}