//
// Created by piptouque on 18/12/2019.
//

#ifndef WORLD_IMAKER_SHADERSENDER_HPP
#define WORLD_IMAKER_SHADERSENDER_HPP

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include <glimac/Programme.hpp>
#include <glimac/FilePath.hpp>


#include "Types.hpp"
#include "Exception.hpp"
#include "Material.hpp"

namespace wim
{;

    static constexpr const char* STORAGE_POSLIGHT_NAME = "sPosLight_vs";
    static constexpr const char* STORAGE_DIRLIGHT_NAME = "sDirLight_vs";


    /* Path to shaders and config file relative to build directory */
    static constexpr const char* DEFAULT_SHADER_DIR = "resources/shaders";
    static constexpr const char* DEFAULT_SHADER_CONF_FILENAME = "shaders.conf";

    /* Constant used in shader files loading?*/
    static const unsigned int MAX_SIZE_SHADER_FILENAME = 30;
    static const char SEP = glimac::FilePath::PATH_SEPARATOR; //defined in FilePath

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

    class ShaderSender
    {
    private:
        ShaderCouple _couple;
        glimac::Programme _programme;
        //light properties (light position is in View Space coordinates)
        /* Only the ID of the property is stored, not the light itself
         * which will change depending on the camera.
         */
        //todo: add support for multiple lights, including directional light.
        GLuint _bAmbiantLightData;
        GLuint _sPointLightData_vs, _sDirLightData_vs;

    private:
        void loadProgramme(const glimac::FilePath& appPathDir, const ShaderCouple& couple);
        void getAllAttrLoc();
    private:
        void initSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple);
    public:
        ShaderSender() = default;
        ShaderSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple);




        void sendStorageBlockBuffer(const GLuint blockTarget, const GLuint bindTarget) const;

        inline void useProgramme() const {_programme.use();}

        inline const glimac::Programme& programme() const {return _programme;}
        inline glimac::Programme& programme() {return _programme;}

        inline const ShaderCouple& couple() const { return _couple;}
        inline ShaderCouple& couple() { return _couple;}


        friend std::ostream& operator<<(std::ostream& stream, const ShaderSender& sender)
        {
            stream << sender._couple << std::endl;
            return stream;
        }

    };

    //typedef for convenience
    typedef std::vector<ShaderSender> ListSender;

}

#endif //WORLD_IMAKER_SHADERSENDER_HPP
