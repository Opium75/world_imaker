//
// Created by piptouque on 24/12/2019.
//

#include "../include/wim/BufferManager.hpp"

#include <algorithm>

namespace wim
{
    BufferManager::BufferManager(const TextureManagerPtr& textures, const WindowManagerPtr& windows) :
            _itos(std::make_shared<ListITO>(textures->getCubeMaps().size())),
            _matrices(DEFAULT_MATRICES_BUFFERSIZE),
            _material(DEFAULT_MATERIAL_BUFFERSIZE),
            _ambiantLight(DEFAULT_AMBIANTLIGHT_BUFFERSIZE),
            _baseTexture(),
            _cubeIndex(),
            _pointLights(DEFAULT_ONE_POINTLIGHT_BUFFERSIZE, MAX_NB_EACH_LIGHT),
            _directionLights(DEFAULT_ONE_DIRECTIONALLIGHT_BUFFERSIZE, MAX_NB_EACH_LIGHT),
            _lightNumber(DEFAULT_LIGHTNUMBER_BUFFERSIZE,1),
            _framebuffer(windows->window(), NB_DEFAULT_DRAWBUFFERS, DEFAULT_DRAWBUFFERS)
    {

        this->loadCubeMaps(textures->getCubeMaps());
    }

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

        //Index of the current drawn cube
        _cubeIndex.localise(shader.programme().getGLId(),
                                UNI_LOC_CUBEINDEX_NAME
        );

        //Texture in framebuffer to be rendered
        _framebuffer.renderUniform().localise(shader.programme().getGLId(),
                            UNI_LOC_FRAMEBUFFERTEXTURE_NAME
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

    void BufferManager::updateFramebuffer()
    {
        _framebuffer.update();
    }

    void BufferManager::updateCubeIndex(const Anchor& anchor) const
    {
            _cubeIndex.updateCubeIndex(anchor);
    }

    void BufferManager::bindShaders(const ShaderManagerPtr& shaders) const
    {
        for( const auto& shader : shaders->listSender() )
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

    void BufferManager::renderSceneToFramebuffer() const
    {
        _framebuffer.renderSceneToFramebuffer();
    }

    void BufferManager::renderFramebufferToScreen() const
    {
        _framebuffer.renderFramebufferToScreen();
    }

    bool BufferManager::readCubeIndex(Anchor& position, const GLint vX, const GLint vY) const
    {
        return _framebuffer.readCubeIndex(position, vX, vY);
    }
}