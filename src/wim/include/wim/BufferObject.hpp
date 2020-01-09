//
// Created by piptouque on 29/12/2019.
//

#ifndef WORLD_IMAKER_BUFFEROBJECT_HPP
#define WORLD_IMAKER_BUFFEROBJECT_HPP

#pragma once


#include "FBO.hpp"
#include "ITO.hpp"
#include "SSBO.hpp"
#include "Uniform.hpp"

namespace wim
{

    /*Names of uniform attributs as they are used in the shaders
  * For now, we will only support one light source. IN POINT LIGHT
  */
    //MATRICES
    static constexpr const char* UNI_BLOCK_MATRICES_NAME = "bMatrices";
    //MATERIAL
    static constexpr const char* UNI_BLOCK_MATERIAL_NAME = "bMaterial";
    //BASE TEXTURE
    static constexpr const char* UNI_LOC_BASETEXTURE_NAME = "uBaseTexture";
    //cube index for selection
    static constexpr const char* UNI_LOC_CUBEINDEX_NAME = "uCubeIndex";
    //FRAMEBUFFER TEXTURE
    static constexpr const char* UNI_LOC_FRAMEBUFFERTEXTURE_NAME = "uFramebuffer";
    /* LIGHTs
     * One ambiant, and multiple point and directional lights
     * (using shader storage buffers; see Light.hpp for storage details.)
     */
    static constexpr const char* UNI_BLOCK_AMBIANTLIGHT_NAME = "bAmbiantLight";

    static constexpr const char* STORAGE_BLOCK_POINTLIGHT_NAME = "sPointLight";
    static constexpr const char* STORAGE_BLOCK_DIRECTIONLIGHT_NAME = "sDirectionLight";
    static constexpr const char* STORAGE_BLOCK_LIGHTNUMBER_NAME = "sLightNumber";


    //UBOs
    static constexpr GLuint BINDING_MATRICES_INDEX = 0;
    static constexpr GLuint BINDING_MATERIAL_INDEX = 1;
    static constexpr GLuint BINDING_AMBIANTLIGHT_INDEX = 2;

    //SSBOs
    static constexpr GLuint BINDING_LIGHTNUMBER_INDEX = 0;
    static constexpr GLuint BINDING_POINTLIGHT_INDEX = 1;
    static constexpr GLuint BINDING_DIRECTIONLIGHT_INDEX = 2;

}

#endif //WORLD_IMAKER_BUFFEROBJECT_HPP
