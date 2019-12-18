//
// Created by piptouque on 18/12/2019.
//

#include "../include/wim/ShaderLoader.hpp"

namespace wim {


    ShaderCouple ShaderCouple::loadCouple(std::ifstream &stream) {
        ShaderCouple couple;
        if (!stream.is_open()) {
            throw Exception(ExceptCode::NULL_POINTER, 1, "Trying to acess empty stream. Is file properly loaded ?");
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


    void ShaderLoader::initShaders() {
        std::ifstream conf;
        std::string confPath = std::string(_appPathDir) + SEP + DEFAULT_SHADER_DIR + SEP + DEFAULT_SHADER_CONF_FILENAME;
        conf.open(confPath);
        if (!conf.is_open())
            throw Exception(ExceptCode::NULL_POINTER, 1, std::string("Could not open file at path: ") + confPath);
        //get expected number of couples
        size_t n;
        conf >> n;
        //ending line
        conf.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //fill vector of Shader Couples
        _vecManagerPtr.reserve(n);
        /*_vecShaderCouple.reserve(n);
         _vecProgramme.reserve(n);
         */
        //do n times
        for (size_t i = 0; i < n; ++i) {
            if (conf.eof())
                throw Exception(ExceptCode::END_OF_FILE, 1, "Number of shaders greater than expected.");

            _vecManagerPtr.push_back(
                    std::make_shared<ShaderManager>(_appPathDir, ShaderCouple::loadCouple(conf))
            );
            /*_vecShaderCouple.push_back(ShaderCouple::loadCouple(conf));
            _vecProgramme.push_back(this->loadProgramme(_vecShaderCouple.back()));
             */

        }
        conf.close();
    }

    glimac::Program ShaderLoader::loadProgramme(const ShaderCouple &couple) {
        std::string shaderCoupleDirPath = std::string(_appPathDir) + SEP + DEFAULT_SHADER_DIR;
        std::cout << shaderCoupleDirPath + SEP + couple._vs << std::endl;
        std::cout << shaderCoupleDirPath + SEP + couple._fs << std::endl;
        return glimac::loadProgram(shaderCoupleDirPath + SEP + couple._vs,
                                   shaderCoupleDirPath + SEP + couple._fs
        );
    }

    void ShaderManager::loadProgramme(const glimac::FilePath &appPathDir, const ShaderCouple &couple)
    {
        std::string shaderCoupleDirPath = std::string(appPathDir) + SEP + DEFAULT_SHADER_DIR;
        std::cout << shaderCoupleDirPath + SEP + couple._vs << std::endl;
        std::cout << shaderCoupleDirPath + SEP + couple._fs << std::endl;
        _programme = glimac::loadProgram(shaderCoupleDirPath + SEP + couple._vs,
                                         shaderCoupleDirPath + SEP + couple._fs
        );


    }
}