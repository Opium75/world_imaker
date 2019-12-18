//
// Created by piptouque on 18/12/2019.
//

#include "../include/wim/ShaderManager.hpp"

namespace wim
{
    void ShaderManager::sendUniAttribMatrix(const glm::mat4& MVMatrix, const glm::mat4& MVPMatrix, const glm::mat4& NormalMatrix) const
    {
        //Only send Matrix attributes to shaders.
        glUniformMatrix4fv(_uMVMatrix,
                           1, //only one matrix sent
                           GL_FALSE, //is it normalised? Nope.
                           glm::value_ptr(MVMatrix)
        );
        glUniformMatrix4fv(_uMVPMatrix,
                           1, //only one matrix sent
                           GL_FALSE,
                           glm::value_ptr(MVPMatrix)
        );
        glUniformMatrix4fv(_uNormalMatrix,
                           1, //only one matrix sent
                           GL_FALSE,
                           glm::value_ptr(NormalMatrix)
        );
    }

    void ShaderManager::sendUniAttribMaterial(const glm::vec3& kD, const glm::vec3& kS, const glm::vec3& shininess) const
    {
        glUniform3fv(_uKd,
                     1,
                     glm::value_ptr(kD)
        );
        glUniform3fv(_uKs,
                     1,
                     glm::value_ptr(kS)
        );
        glUniform3fv(_uShininess,
                     1,
                     glm::value_ptr(shininess)
        );

    }

    void ShaderManager::sendUniAttribLight(const glm::vec3& lightPos_vs, const glm::vec3& lightIntensity) const
    {
        glUniform3fv(_uLightPos_vs,
                     1,
                     glm::value_ptr(lightPos_vs)
        );
        glUniform3fv(_uLightIntensity,
                     1,
                     glm::value_ptr(lightIntensity)
        );
    }


    void ShaderManager::loadUniAttrLoc()
    {
        //
        _uMVPMatrix = glGetUniformLocation(_programme.getGLId(), UNI_MVP_NAME);
        _uMVMatrix = glGetUniformLocation(_programme.getGLId(), UNI_MV_NAME);
        _uNormalMatrix = glGetUniformLocation(_programme.getGLId(), UNI_NORMAL_NAME);
        //
        _uKd = glGetUniformLocation(_programme.getGLId(), UNI_KD_NAME);
        _uKs = glGetUniformLocation(_programme.getGLId(), UNI_KS_NAME);
        _uShininess = glGetUniformLocation(_programme.getGLId(), UNI_SHININESS_NAME);
        //
        _uLightPos_vs = glGetUniformLocation(_programme.getGLId(), UNI_LIGHTPOS_NAME);
        _uLightIntensity = glGetUniformLocation( _programme.getGLId(), UNI_LIGHTINTENSITY_NAME);
    }
}