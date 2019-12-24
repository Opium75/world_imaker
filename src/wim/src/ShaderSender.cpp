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


    void ShaderSender::getAllAttrLoc()
    {
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