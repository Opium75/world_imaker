//
// Created by piptouque on 24/12/2019.
//

#include "../include/wim/BufferManager.hpp"

#include <string>
#include <algorithm>

namespace wim
{


    void BufferManager::bindShader(const ShaderSender& shader) const
    {
        //MATRICES
        _matrices.bind(shader.programme().getGLId(),
                       UNI_BLOCK_MATRICES_NAME,
                       BINDING_MATRICES_INDEX
        );
        //MATERIAL
        _material.bind(shader.programme().getGLId(),
                       UNI_BLOCK_MATERIAL_NAME,
                       BINDING_MATERIAL_INDEX
        );

        //AMBIANT LIGHT
        _ambiantLight.bind(shader.programme().getGLId(),
                           UNI_BLOCK_AMBIANTLIGHT_NAME,
                           BINDING_AMBIANTLIGHT_INDEX
        );

        //POINT AND DIRECTIONAL LIGHTS
        _pointLights.bind(shader.programme().getGLId(),
                          STORAGE_BLOCK_POINTLIGHT_NAME,
                          BINDING_POINTLIGHT_INDEX
        );
        _directionLights.bind(shader.programme().getGLId(),
                                STORAGE_BLOCK_DIRECTIONLIGHT_NAME,
                                BINDING_DIRECTIONLIGHT_INDEX
        );

        _lightNumber.bind(shader.programme().getGLId(),
                            STORAGE_BLOCK_LIGHTNUMBER_NAME,
                            BINDING_LIGHTNUMBER_INDEX
                            );
    }

    void BufferManager::localiseUniform(const ShaderSender& shader)
    {
        //BASE TEXTURE
        _baseTexture.localise(shader.programme().getGLId(),
                              UNI_LOC_BASETEXTURE_NAME
        );
    }

    void BufferManager::updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj ) const
    {

        CameraMatricesData data(MV, Proj );
        _matrices.update(&data, sizeof(data));
    }

    void BufferManager::updateMaterial(const Material& material, const bool isTextured) const
    {
        MaterialData data(material, isTextured);
        _material.update(&data, sizeof(MaterialData));
    }

    void BufferManager::updateLights(const LightManager &lights, const UniformMatrix& View) const
    {
        this->updateAmbiantLight(lights.ambiant());
        this->updatePointLights(lights.listPoint(), View);
        this->updateDirectionLights(lights.listDirection(), View);
        this->updateLightNumber(lights.listPoint(), lights.listDirection());
    }

    void BufferManager::updateAmbiantLight(const AmbiantLight &ambiant) const
    {
        AmbiantLightData data(ambiant);
        _ambiantLight.update(&data, sizeof(AmbiantLightData));
    }

    void BufferManager::updatePointLights(const ListPLight& pLights, const UniformMatrix& View) const
    {
        ListPLightData data(pLights.begin(), pLights.end());
        //from model to view:
        std::for_each(data.begin(), data.end(),
                      [View](PointLightData& data) {data.origin() = View*data.origin();}
        );
        _pointLights.update(data.data(), sizeof(PointLightData), data.size() );

    }
    void BufferManager::updateDirectionLights(const ListDLight& dLights, const UniformMatrix& View) const
    {
        ListDLightData data(dLights.begin(), dLights.end());
        //from model to view:
        std::for_each(data.begin(), data.end(),
                [View](DirectionLightData &data) {data.direction() = View*data.direction();}
                );
        _directionLights.update(data.data(), sizeof(DirectionLightData), data.size() );
    }

    void BufferManager::updateLightNumber(const ListPLight &pLights, const ListDLight &dLights) const
    {
        LightNumberData data(pLights.size(), dLights.size());
        _lightNumber.update(&data, sizeof(LightNumberData), 1);
    }

    void BufferManager::bindShaders(const ListSender& shaders) const
    {
        for( const auto& shader : shaders )
        {
            this->bindShader(shader);
        }
    }

    void BufferManager::loadCubeMaps(const ListCubeMap &cubeMaps) const
    {
        SizeInt index = 0;
        std::for_each(cubeMaps.begin(), cubeMaps.end(),
                    [this, &index](const CubeMap& cubeMap)
                    {this->loadCubeMap(index++, cubeMap);}
        );
    }

    void BufferManager::loadCubeMap(const SizeInt indexTexture, const CubeMap& cubeMap) const
    {
        for(SizeInt indexFace=0; indexFace<cubeMap.getNumberFaces(); ++indexFace)
            this->loadFace(indexFace, indexTexture, cubeMap);
    }

    void BufferManager::loadFace(const SizeInt indexFace, const SizeInt indexTexture, const CubeMap& cubeMap) const
    {
        _itos->at(indexTexture).loadFace(
                indexFace,
                cubeMap.getPixels(indexFace),
                cubeMap.getWidth(indexFace),
                cubeMap.getHeight(indexFace)
        );
    }


}