//
// Created by piptouque on 18/12/2019.
//

#include "wim/ShaderSender.hpp"

namespace wim
{

    void ShaderSender::initSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple)
    {
        this->loadProgramme(appPathDir, couple);
        this->getAllUniAttrLoc();
    }

    void ShaderSender::loadProgramme(const glimac::FilePath &appPathDir, const ShaderCouple &couple)
    {
        std::string shaderCoupleDirPath = std::string(appPathDir) + SEP + DEFAULT_SHADER_DIR;
        std::cout << shaderCoupleDirPath + SEP + couple._vs << std::endl;
        std::cout << shaderCoupleDirPath + SEP + couple._fs << std::endl;
        _programme = glimac::loadProgramme(shaderCoupleDirPath + SEP + couple._vs,
                                         shaderCoupleDirPath + SEP + couple._fs
        );


    }

    void ShaderSender::sendUniAttribMatrix4(const GLint uniTarget, const glm::mat4 &M) const
    {
       glUniformMatrix4fv(uniTarget,
                    1, //only one matrix sent
                    GL_FALSE, //is it normalised? ?pê
                    glm::value_ptr(M)
               );
    }

    void ShaderSender::sendUniAttribVec3(const GLint uniTarget, const glm::vec3& vec) const
    {
        glUniform3fv(uniTarget, 1, glm::value_ptr(vec));
    }

    void ShaderSender::sendUniAttribFloat(const GLint uniTarget, const GLfloat value) const
    {
        glUniform1f(uniTarget, value);
    }

    void ShaderSender::sendMVPNMatrices(const glm::mat4& MVMatrix, const glm::mat4& ProjMatrix, const glm::mat4& NormalMatrix) const
    {
        //Only send Matrix attributes to shaders.
        this->sendUniAttribMatrix4(_uMVMatrix, MVMatrix);
        this->sendUniAttribMatrix4(_uMVPMatrix, ProjMatrix*MVMatrix);
        this->sendUniAttribMatrix4(_uNormalMatrix, NormalMatrix);
    }

    void ShaderSender::sendMaterial(const glm::vec3& kD, const glm::vec3& kS, const GLfloat shininess) const
    {
        this->sendUniAttribVec3(_uKd, kD);
        this->sendUniAttribVec3(_uKs, kS);
        this->sendUniAttribFloat(_uShininess, shininess);
    }

    void ShaderSender::sendLight(const glm::vec3& lightPos_vs, const glm::vec3& lightIntensity) const
    {
        this->sendUniAttribVec3(_uLightPos_vs, lightPos_vs);
        this->sendUniAttribVec3(_uLightIntensity, lightIntensity);
    }


    void ShaderSender::getAllUniAttrLoc()
    {
        _uNormalMatrix = glGetUniformLocation(_programme.getGLId(), UNI_NORMAL_NAME);
        _uMVMatrix = glGetUniformLocation(_programme.getGLId(), UNI_MV_NAME);
        _uMVPMatrix = glGetUniformLocation(_programme.getGLId(), UNI_MVP_NAME);
        //
        _uKd = glGetUniformLocation(_programme.getGLId(), UNI_KD_NAME);
        _uKs = glGetUniformLocation(_programme.getGLId(), UNI_KS_NAME);
        _uShininess = glGetUniformLocation(_programme.getGLId(), UNI_SHININESS_NAME);
        //
        _uLightPos_vs = glGetUniformLocation(_programme.getGLId(), UNI_LIGHTPOS_NAME);
        _uLightIntensity = glGetUniformLocation( _programme.getGLId(), UNI_LIGHTINTENSITY_NAME);
    }



    ShaderCouple ShaderCouple::loadCouple(std::ifstream &stream) {
        ShaderCouple couple;
        if (!stream.is_open()) {
            throw Exception(ExceptCode::NULL_POINTER, 1, "Trying to access empty stream. Is file properly loaded ?");
        }
        //vs, then fs
        char *buffer = new char[MAX_SIZE_SHADER_FILENAME];
        stream.getline(buffer, MAX_SIZE_SHADER_FILENAME, ' ');
        couple._vs = std::string(buffer);
        stream.getline(buffer, MAX_SIZE_SHADER_FILENAME, '\n');
        couple._fs = std::string(buffer);
        delete[] buffer;

        return couple;
    }
}