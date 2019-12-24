//
// Created by piptouque on 24/12/2019.
//

#include "../include/wim/BufferManager.hpp"

namespace wim
{


    void BufferManager::bindShader(const ShaderSender& shader) const
    {
        //MATRICES
        this->_matrices.bindBlock(shader.programme().getGLId(),
                                  UNI_BLOCK_MATRICES_NAME,
                                  BINDING_MATERIAL_INDEX
        );
        //MATERIAL
        this->_material.bindBlock(shader.programme().getGLId(),
                                  UNI_BLOCK_MATERIAL_NAME,
                                  BINDING_MATERIAL_INDEX
        );
        //AMBIANT LIGHT
        this->_ambiantLight.bindBlock(shader.programme().getGLId(),
                                      UNI_BLOCK_AMBIANTLIGHT_NAME,
                                      BINDING_AMBIANTLIGHT_INDEX
        );
    }

    void BufferManager::allocAllUniBuffers() const
    {
        //MATRICES
        this->_matrices.alloc(DEFAULT_MATRICES_BUFFERSIZE);
        this->_material.alloc(DEFAULT_MATERIAL_BUFFERSIZE);
        this->_ambiantLight.alloc(DEFAULT_AMBIANTLIGHT_BUFFERSIZE);
    }

    void BufferManager::bindAllUBO() const
    {
        this->_matrices.bindObject(BINDING_MATRICES_INDEX);
        this->_material.bindObject(BINDING_MATERIAL_INDEX);
        this->_ambiantLight.bindObject(BINDING_AMBIANTLIGHT_INDEX);
    }

    void BufferManager::updateVec3Only(const UBO& object, const glm::vec3& vec, const SizeInt indexOffset) const
    {
        object.update(glm::value_ptr(vec), indexOffset*sizeof(glm::vec4), sizeof(glm::vec3));
    }

    void BufferManager::updateFloatLast(const UBO& object, const GLfloat value, const SizeInt indexOffset) const
    {
        object.update(&value, indexOffset* sizeof(glm::vec4), sizeof(GLfloat));
    }

    void BufferManager::updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj) const
    {
        this->updateMatrix( Proj*MV, 0);
        this->updateMatrix( MV, 1);
        this->updateMatrix( glm::transpose(glm::inverse(MV)), 2);
    }

    void BufferManager::updateMaterial(const Material& material) const
    {
        //colour
        this->updateVec3Only(_material, material.colour().getCoord(), 0);
        //ks et ks
        this->updateVec3Only(_material, material.kD().getCoord(), 1);
        this->updateVec3Only(_material, material.kS().getCoord(), 2);
        //shininess
        this->updateFloatLast(_material, material.shininess(), 3);

    }

    void BufferManager::updateAmbiantLight(const AmbiantLightData &ambiant) const
    {
        //colour
        this->updateVec3Only(_ambiantLight, ambiant._colour, 0);
        this->updateFloatLast(_ambiantLight, ambiant._intensity, 1);
    }

    void BufferManager::init(const ListSender& shaders) const
    {
        for( const auto& shader : shaders )
        {
            this->bindShader(shader);
        }

        this->allocAllUniBuffers();
        this->bindAllUBO();
    }
}