//
// Created by piptouque on 24/12/2019.
//

#ifndef WORLD_IMAKER_BUFFERMANAGER_HPP
#define WORLD_IMAKER_BUFFERMANAGER_HPP

#pragma once

#include <vector>
#include <memory>

#include "CommonDisplay.hpp"
#include "Displayable.hpp"
#include "Types.hpp"

#include "BufferObject.hpp"
#include "BufferData.hpp"

#include "ShaderSender.hpp"
#include "ShaderManager.hpp"

#include "TextureManager.hpp"

#include "Light.hpp"
#include "Material.hpp"

namespace wim
{


    class BufferManager
    {
    public:
    private:
        ListITOPtr _itos;
        UBO _matrices, _material, _ambiantLight;
        Uniform _baseTexture, _baseColour, _cubeIndex;
        SSBO _pointLights, _directionLights;
        SSBO _lightNumber;
        FBO _framebuffer;
    public:

        BufferManager(const TextureManagerPtr& textures, const WindowManagerPtr& windows);
        ~BufferManager() = default;


        ///brief; update MV, MVP, Normal and View matrices to shaders
        void updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj ) const;
        void updateMaterial(const Material& material, const bool isTextured) const;
        void updateLights(const LightManager& lights, const UniformMatrix& View ) const;
        void updateFramebuffer();
        void updateCubeIndex(const Point3Uint& anchor) const;

        void bindShaders(const ShaderManagerPtr& shaders) const;
        void localiseUniform(const ShaderSender& shader);

        void loadCubeMaps(const ListCubeMap& cubeMaps) const;

        inline const ListITOPtr& getListITO() const {return _itos;}
        inline const FBO& getFramebuffer() const {return _framebuffer;}

        void renderSceneToFramebuffer() const;
        void renderFramebufferToScreen() const;

        bool readCubeIndex(Point3Uint& position, const GLint vX, const GLint vY) const;

    private:
        void updateAmbiantLight(const AmbiantLight& ambiant) const;
        void updateLightNumber(const ListPLight& pLights, const ListDLight& dLights) const;
        void updatePointLights(const ListPLight& pLights, const UniformMatrix& View) const;
        void updateDirectionLights(const ListDLight& dLights, const UniformMatrix& View) const;


        void loadCubeMap(const SizeInt indexTexture, const CubeMap& cubeMap) const;
        void loadFace(const SizeInt indexFace, const SizeInt indexTexture, const CubeMap& cubeMap) const;

        void bindShader(const ShaderSender& shader) const;
    };

    typedef std::unique_ptr<BufferManager> BufferManagerPtr;
}

#endif //WORLD_IMAKER_BUFFERMANAGER_HPP
