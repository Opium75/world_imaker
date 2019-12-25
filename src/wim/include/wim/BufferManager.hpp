//
// Created by piptouque on 24/12/2019.
//

#ifndef WORLD_IMAKER_BUFFERMANAGER_HPP
#define WORLD_IMAKER_BUFFERMANAGER_HPP

#pragma once

#include "CommunDisplay.hpp"
#include "ShaderSender.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Types.hpp"

namespace wim
{

    struct CameraMatricesData
    {
        UniformMatrix _MVP, _MV, _Normal;
        CameraMatricesData(const UniformMatrix& MV, const UniformMatrix& Proj) :
            _MVP(Proj*MV), _MV(MV), _Normal(glm::transpose(glm::inverse(MV)))
        {
        }
    };

    struct MaterialData
    {
        glm::vec4 _colour, _kD;
        glm::vec3 _kS;
        GLfloat _shininess;
        MaterialData(const Material& material) :
            _colour(material.colour().getCoord(),0), _kD(material.kD().getCoord(),0), _kS(material.kS().getCoord()), _shininess(material.shininess())
        {
        }
    };

    struct AmbiantLightData
    {
        glm::vec3 _colour;
        GLfloat _intensity;
        AmbiantLightData(const AmbiantLight& ambiant):
            _colour(ambiant.colour().getCoord()), _intensity(ambiant.intensity())
        {
        }
    };


    /*Names of uniform attributs as they are used in the shaders
     * For now, we will only support one light source. IN POINT LIGHT
     */
    //MATRICES
    static constexpr const char* UNI_BLOCK_MATRICES_NAME = "bMatrices";
    //MATERIAL
    static constexpr const char* UNI_BLOCK_MATERIAL_NAME = "bMaterial";
    /* LIGHTs
     * One ambiant, and multiple point and directional lights
     * (using shader storage buffers; see Light.hpp for storage details.)
     */
    static constexpr const char* UNI_BLOCK_AMBIANTLIGHT_NAME = "bAmbiantLight";
    /* SEE STD140 FOR DETAILS ON OFFSETS AND SIZES
     * AS HANDLED BY GLSL
     */

    static const GLuint BINDING_MATRICES_INDEX = 0;
    static const GLuint BINDING_MATERIAL_INDEX = 1;
    static const GLuint BINDING_AMBIANTLIGHT_INDEX = 2;
    static const GLuint BINDING_POSLIGHT_INDEX = 3;
    static const GLuint BINDING_DIRLIGHT_INDEX = 4;

    //todo: find a way to get required sizes
    static const GLsizeiptr GLSL_STD140_FLOAT = 4;//in bytes
    static const GLsizeiptr GLSL_STD140_VEC3 = 16;
    static const GLsizeiptr GLSL_STD140_MAT4 = 64;
    static const GLsizeiptr DEFAULT_MATRICES_BUFFERSIZE = sizeof(CameraMatricesData);
    static const GLsizeiptr DEFAULT_MATERIAL_BUFFERSIZE = sizeof(MaterialData);
    static const GLsizeiptr DEFAULT_AMBIANTLIGHT_BUFFERSIZE = 2*sizeof(AmbiantLightData);


    struct UBO
    {
    public:
        GLuint _ubo;
    public:
        UBO(const GLsizeiptr size) : _ubo()
        {
            glGenBuffers(1, &_ubo);
            this->alloc(size);

        }
        ~UBO() {glDeleteBuffers(1,&_ubo);}


        void bind(const GLuint programme, const char* UNI_BUFFER_NAME, const GLuint binding) const;
        void alloc(const GLsizeiptr size) const;
        void update(const GLvoid* data,  const GLsizeiptr size) const;
    private:
        void bindBlock(const GLuint programme, const char* UNI_BUFFER_NAME, const GLuint binding) const;
        void bindObject(const GLuint binding) const;
    };

    struct SSBO
    {
    public:
        GLuint _ssbo;
    public:
        SSBO() : _ssbo()
        {
            glGenBuffers(1, &_ssbo);

        }
        ~SSBO()
        {
            glDeleteBuffers(1, &_ssbo);
        }

        void buildObject(const GLvoid* data, const GLsizeiptr size) const
        {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
                glBufferData(GL_SHADER_STORAGE_BUFFER,
                            size,
                             data,
                             GL_DYNAMIC_COPY
                );
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        }

        void updateObject(const GLvoid* data, const GLsizeiptr size) const
        {
            GLvoid *bufferPtr;
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
                bufferPtr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
                    std::memcpy(bufferPtr,
                            data,
                            size);
                glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
            //todo: Check if unbinding here is a mistake.
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        }
    };

    class BufferManager
    {
        UBO _matrices, _material, _ambiantLight;

    public:

        BufferManager() :
            _matrices(DEFAULT_MATRICES_BUFFERSIZE),
            _material(DEFAULT_MATERIAL_BUFFERSIZE),
            _ambiantLight(DEFAULT_AMBIANTLIGHT_BUFFERSIZE)
        {

        }
        ~BufferManager() = default;


        ///brief; update modelview, modevviewprojection (from projection and modelview), and normal matrices to shaders
        void updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj) const;
        void updateMaterial(const Material& material) const;
        void updateAmbiantLight(const AmbiantLight& ambiant) const;

        void bindShaders(const ListSender& shaders) const;

    private:
        void bindShader(const ShaderSender& shader) const;
     /*   void updateMatrix(const UniformMatrix& m, SizeInt indexoffset) const;
        void updateVec3Only(const UBO& object, const glm::vec3& vec, const SizeInt indexoffset) const;
        void updateFloatLast(const UBO& object, const GLfloat value, const SizeInt indexoffset) const;
        */

    };
}

#endif //WORLD_IMAKER_BUFFERMANAGER_HPP
