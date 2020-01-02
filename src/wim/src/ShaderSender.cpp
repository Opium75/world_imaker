//
// Created by piptouque on 18/12/2019.
//

#include "wim/ShaderSender.hpp"

namespace wim
{

    ShaderSender::ShaderSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple) : _couple(couple), _programme()
    {

        this->initSender(appPathDir, _couple);
        //use first programme to begin with ?
        //Nope, will be decided by ShaderManager.
    }

    void ShaderSender::initSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple)
    {
        this->loadProgramme(appPathDir, couple);
    }

    void ShaderSender::loadProgramme(const glimac::FilePath &appPathDir, const ShaderCouple &couple)
    {
        std::string shaderCoupleDirPath = std::string(appPathDir) + SEP + DEFAULT_RESOURCES_DIR + SEP + DEFAULT_SHADER_DIR;
        _programme = glimac::loadProgramme(shaderCoupleDirPath + SEP + couple._vs,
                                         shaderCoupleDirPath + SEP + couple._fs
        );
    }




    ShaderCouple ShaderCouple::loadCouple(std::ifstream &conf) {
        ShaderCouple couple;
        if (!conf.is_open()) {
            throw Exception(ExceptCode::NULL_POINTER, 1, "Trying to access empty stream. Is file properly loaded ?");
        }
        //vs, then fs
        std::string buffer;
        conf >> buffer;
        couple._vs = buffer;
        buffer.clear();
        conf >> buffer;
        couple._fs = buffer;
        return couple;
    }
}