//
// Created by piptouque on 17/12/2019.
//

#ifndef WORLD_IMAKER_SHADERLOADER_HPP
#define WORLD_IMAKER_SHADERLOADER_HPP

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <memory>



#include <glimac/Program.hpp>

#include "ShaderManager.hpp"
#include "Exception.hpp"

namespace wim
{

    const std::string DEFAULT_SHADER_DIR("resources/shaders");
    const std::string DEFAULT_SHADER_CONF_FILENAME("shaders.conf");
    const unsigned int MAX_SIZE_SHADER_FILENAME = 15;
    const char SEP = glimac::FilePath::PATH_SEPARATOR; //defined in FilePath

    struct ShaderCouple
    {
    public:
        std::string _vs, _fs;

    public:
        ///brief: Read vertex and fragment shaders from formatted input
        static ShaderCouple loadCouple(std::ifstream& stream);

        friend std::ostream& operator<<(std::ostream& stream, const ShaderCouple& couple)
        {
            stream << "vs: " << couple._vs << " /\\ fs: " << couple._fs;
            return stream;
        }

    };

    //two typedefs for convenience
    typedef std::vector<ShaderCouple> ListCouple;
    typedef std::vector<glimac::Program> ListProgramme;
    typedef std::vector<std::shared_ptr<ShaderManager>> ListManagerPtr;

    class ShaderLoader
    {
    public:

    private:
        glimac::FilePath _appPathDir;
        /* One for every set of shaders */
        ListManagerPtr  _vecManagerPtr;




    public:
        ShaderLoader() = default;

        ShaderLoader(const glimac::FilePath& appPath) : _appPathDir(glimac::FilePath(appPath).dirPath().dirPath())
        {
           this->initShaders();
           this->useProgramme(0);
        }

        void initShaders();


        glimac::Program loadProgramme(const ShaderCouple& couple);


        inline void useProgramme(const size_t index) const { _vecProgramme.at(index).use();}

        inline glimac::Program& programme(const size_t index) { return _vecProgramme.at(index);}
        inline const glimac::Program& programme(const size_t index) const { return _vecProgramme.at(index);}

        inline ShaderCouple& couple(const size_t index) {return _vecShaderCouple.at(index);}
        inline const ShaderCouple& couple(const size_t index) const {return _vecShaderCouple.at(index);}

       /* friend std::ostream& operator<<(std::ostream& stream, const ListCouple& vecShaderCouple)
        {
            for(const auto& couple : vecShaderCouple)
            {
                stream << couple << std::endl;
            }

            return stream;
        }*/

        friend std::ostream& operator<<(std::ostream& stream, const ShaderLoader& loader)
        {
       // stream << loader._vecShaderCouple;

            for(const auto& couple : loader._vecShaderCouple)
            {
                stream << couple << std::endl;
            }


            return stream;
        }
    };
}

#endif //WORLD_IMAKER_SHADERLOADER_HPP
