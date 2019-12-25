//
// Created by piptouque on 18/12/2019.
//

#include "wim/ShaderManager.hpp"

namespace wim {



    void ShaderManager::readConfig()
    {
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
        _listSender.reserve(n);
        //do n times
        for (size_t i = 0; i < n; ++i) {
            std::string strShader;
            if (conf.eof())
                throw Exception(ExceptCode::END_OF_FILE, 1,
                        std::string("Fewer shader couples than expected: expected ")
                        + std::to_string(n) + std::string(", found ") + std::to_string(i)
                        );
            _listSender.push_back(
                    ShaderSender(_appPathDir, ShaderCouple::loadCouple(conf))
            );
        }
        conf.close();
    }




}