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


#include <vector>

#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>


#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

#include "ShaderManager.hpp"
#include "Exception.hpp"

namespace wim
{

    const std::string DEFAULT_SHADER_DIR("resources/shaders");
    const std::string DEFAULT_SHADER_CONF_FILENAME("shaders.conf");
    const unsigned int MAX_SIZE_SHADER_FILENAME = 15;
    const char SEP = glimac::FilePath::PATH_SEPARATOR; //defined in FilePath

    /*Names of uniform attributs as they are used in the shaders
     * For now, we will only support one light source. IN POINT LIGHT
     */
    //MATRIX
    constexpr static const char* UNI_MVP_NAME = "uMVPMatrix";
    constexpr static const char* UNI_MV_NAME = "uMVMatrix";
    constexpr static const char* UNI_NORMAL_NAME = "uNormalMatrix";
    //MATERIAL
    constexpr static const char* UNI_KD_NAME = "uNormalMatrix";
    constexpr static const char* UNI_KS_NAME = "uNormalMatrix";
    constexpr static const char* UNI_SHININESS_NAME = "uNormalMatrix";
    //LIGHT
    constexpr static const char* UNI_LIGHTPOS_NAME = "uLightPos_vs";
    constexpr static const char* UNI_LIGHTINTENSITY_NAME = "uLightPos_vs";

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


    class ShaderManager
    {
    private:
        ShaderCouple _couple;
        glimac::Program _programme;
        //Matrix for transformations
        GLint _uMVPMatrix, _uMVMatrix, _uNormalMatrix;
        //for Blinn-Phong, properties of the material
        GLint _uKd, _uKs, _uShininess;
        //light properties (light position is in View Space coordinates)
        /* Only the ID of the property is stored, not the light itself
         * which will change depending on the camera.
         */
        GLint _uLightPos_vs, _uLightIntensity;
    public:
        ShaderManager() = default;
        ShaderManager(const glimac::FilePath& appPathDir, const ShaderCouple& couple) : _couple(couple), _programme()
        {
            this->initManager(appPathDir, couple);
            //use first programme to begin with.
            this->useShaders();
        }

        void initManager(const glimac::FilePath& appPathDir, const ShaderCouple& couple)
        {
            this->loadProgramme(appPathDir, couple);
            this->loadUniAttrLoc();
        }

        void sendUniAttribMatrix(const glm::mat4& MVMatrix, const glm::mat4& MVPMatrix, const glm::mat4& NormalMatrix) const;


        void sendUniAttribMaterial(const glm::vec3& kD, const glm::vec3& kS, const glm::vec3& shininess) const;


        void sendUniAttribLight(const glm::vec3& lightPos_vs, const glm::vec3& lightIntensity) const;

        inline void useShaders() const {_programme.use();}

        friend std::ostream& operator<<(std::ostream& stream, const ShaderManager& manager)
        {
            stream << manager._couple << std::endl;
            return stream;
        }

    private:
        void loadProgramme(const glimac::FilePath& appPathDir, const ShaderCouple& couple);

        void loadUniAttrLoc();
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


        inline void useProgramme(const size_t index) const { _vecManagerPtr.at(index).get()->useShaders();}

        inline glimac::Program& programme(const size_t index) {return _vecManagerPtr.at(index).get()->getProgramme();}
        inline const glimac::Program& programme(const size_t index) const {return _vecManagerPtr.at(index).get()->getProgramme();}

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

    };


}

#endif //WORLD_IMAKER_SHADERLOADER_HPP
