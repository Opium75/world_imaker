//
// Created by piptouque on 23/12/2019.
//

#include "../include/wim/Light.hpp"


namespace wim
{

    AmbiantLight& AmbiantLight::operator=(const AmbiantLight& ambiant)
    {
        _intensity = ambiant._intensity;
        return *this;
    }
    PointLight& PointLight::operator=(const PointLight& pLight)
    {
        _intensity = pLight._intensity;
        _origin = pLight._origin;
        return *this;
    }
    DirectionLight& DirectionLight::operator=(const DirectionLight& dLight)
    {
        _intensity = dLight._intensity;
        _direction = dLight._direction;
        return *this;
    }

        void LightManager::CBaddPoint(const PointLight& pLight)
    {
        if( _listPoint.size() >= MAX_NB_EACH_LIGHT )
            throw Exception(ExceptCode::OVER, 1, "Maximum number of point lights reached." );
        _listPoint.push_back(pLight);
    }
    void LightManager::CBaddDir(const DirectionLight& dLight)
    {
        if( _listDirection.size() >= MAX_NB_EACH_LIGHT )
            throw Exception(ExceptCode::OVER, 1, "Maximum number of directional lights reached." );
        _listDirection.push_back(dLight);
    }
    void LightManager::CBremovePoint(const size_t index)
    {
        if( index >= _listPoint.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Point light at index does not exist." );
        _listPoint.erase(_listPoint.begin()+index);
    }
    void LightManager::CBremoveDir(const size_t index)
    {
        if( index >= _listDirection.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Directional light at index does not exist." );
        _listDirection.erase(_listDirection.begin()+index);
    }

    void LightManager::CBsetAmbiant(const AmbiantLight &ambiant)
    {
        _ambiant = ambiant;
    }

    void LightManager::addDir(const DirectionLight& dLight)
    {
        try
        {
            this->CBaddDir(dLight);
        }
        catch(Exception& e)
        {
            throw;
        }
    }

    void LightManager::addPoint(const PointLight& pLight)
    {
        try
        {
            this->CBaddPoint(pLight);
        }
        catch(Exception& e)
        {
            throw;
        }
    }
    void LightManager::removePoint(const SizeInt index)
    {
        try
        {
            this->CBremovePoint(index);
        }
        catch(Exception& e)
        {
            throw;
        }
    }
    void LightManager::removeDir(const SizeInt index)
    {
        try {
            this->CBremoveDir(index);
        }
        catch (Exception &e) {
            throw;
        }
    }

    void LightManager::setAmbiant(const AmbiantLight &ambiant)
    {
        this->CBsetAmbiant(ambiant);
    }

    AmbiantLight AmbiantLight::Random()
    {
        return AmbiantLight(Colour::Random());
    }

    PointLight PointLight::Random()
    {
        return PointLight(AmbiantLight::Random(),
                Vec3D::Random(0,40)
        );
    }

    DirectionLight DirectionLight::Random()
    {
        return DirectionLight(AmbiantLight::Random(),
                Vec3D::Random()
                );
    }
    LightManager::LightManager() :
        _listPoint(), _listDirection(), _ambiant(AmbiantLight::Random())
    {
        //Enough space for lights
        _listPoint.reserve(MAX_NB_EACH_LIGHT);
        _listDirection.reserve(MAX_NB_EACH_LIGHT);
        /* */
    };

}