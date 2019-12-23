//
// Created by piptouque on 18/12/2019.
//

#include "wim/ShaderSender.hpp"

namespace wim
{

    ShaderSender::ShaderSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple) : _couple(couple), _programme()
    {
        //checking for an error in creating the OpenGL programme
        if( _programme.getGLId()  == 0 )
            throw Exception(ExceptCode::INIT_ERROR, 1, "Could not create OpenGL programme.");
        this->initSender(appPathDir, couple);
        //use first programme to begin with ?
        //Nope, will be decided by ShaderManager.
        //this->useProgramme();
    }

    void ShaderSender::initSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple)
    {
        this->loadProgramme(appPathDir, couple);
        this->getAllAttrLoc();
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

    void ShaderSender::sendStorageBlockBuffer(const GLuint blockTarget, GLuint bindTarget) const
    {
        glShaderStorageBlockBinding(_programme.getGLId(), blockTarget, bindTarget);
    }

    void ShaderSender::sendUniAttribMatrix4(const GLuint uniTarget, const glm::mat4 &M) const
    {
       glUniformMatrix4fv(uniTarget,
                    1, //only one matrix sent
                    GL_FALSE, //is it normalised? ?pê
                    glm::value_ptr(M)
               );
    }

    void ShaderSender::sendUniAttribVec3(const GLuint uniTarget, const glm::vec3& vec) const
    {
        glUniform3fv(uniTarget, 1, glm::value_ptr(vec));
    }

    void ShaderSender::sendUniAttribFloat(const GLuint uniTarget, const GLfloat value) const
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

    void ShaderSender::sendMaterial(const Material& material)
    {
        this->sendUniAttribVec3(_uColour, material.colour().getCoord());
        this->sendUniAttribVec3(_uKd, material.kD().getCoord());
        this->sendUniAttribVec3(_uKs, material.kS().getCoord());
        this->sendUniAttribFloat(_uShininess, material.shininess());

    }

    void ShaderSender::sendLights() const
    {
        this->sendStorageBlockBuffer(_sPointLightData_vs, BINDING_POSLIGHT_INDEX);
        this->sendStorageBlockBuffer(_sDirLightData_vs, BINDING_DIRLIGHT_INDEX);
    }


    void ShaderSender::getAllAttrLoc()
    {
        _uNormalMatrix = glGetUniformLocation(_programme.getGLId(), UNI_NORMAL_NAME);
        _uMVMatrix = glGetUniformLocation(_programme.getGLId(), UNI_MV_NAME);
        _uMVPMatrix = glGetUniformLocation(_programme.getGLId(), UNI_MVP_NAME);
        //
        _uKd = glGetUniformLocation(_programme.getGLId(), UNI_KD_NAME);
        _uKs = glGetUniformLocation(_programme.getGLId(), UNI_KS_NAME);
        _uShininess = glGetUniformLocation(_programme.getGLId(), UNI_SHININESS_NAME);
        //
        _uAmbiantLightData = glGetUniformLocation(_programme.getGLId(), UNI_AMBIANT_NAME);
        //
        _sPointLightData_vs = glGetProgramResourceIndex(_programme.getGLId(), GL_SHADER_STORAGE_BLOCK, STORAGE_POSLIGHT_NAME);
        _sDirLightData_vs = glGetProgramResourceIndex(_programme.getGLId(), GL_SHADER_STORAGE_BLOCK, STORAGE_DIRLIGHT_NAME);

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