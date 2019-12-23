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
{
    /*Names of uniform attributs as they are used in the shaders
     * For now, we will only support one light source. IN POINT LIGHT
     */
    //MATRIX
   static constexpr const char* UNI_MVP_NAME = "uMVPMatrix";
    static constexpr const char* UNI_MV_NAME = "uMVMatrix";
    static constexpr const char* UNI_NORMAL_NAME = "uNormalMatrix";
    //MATERIAL
    static constexpr const char* UNI_KD_NAME = "uKd";
    static constexpr const char* UNI_KS_NAME = "uKs";
    static constexpr const char* UNI_SHININESS_NAME = "uShininess";
    /* LIGHTs
     * One ambiant, and multiple point and directional lights
     * (using shader storage buffers; see Light.hpp for storage details.)
     */
    static constexpr const char* UNI_AMBIANT_NAME = "uAmbiantLightData";
    static constexpr const char* STORAGE_POSLIGHT_NAME = "sPosLightData_vs";
    static constexpr const char* STORAGE_DIRLIGHT_NAME = "sDirLightData_vs";
    static const GLuint BINDING_POSLIGHT_INDEX = 0;
    static const GLuint BINDING_DIRLIGHT_INDEX = 1;


    /* Path to shaders and config file relative to build directory */
    static constexpr const char* DEFAULT_SHADER_DIR = "resources/shaders";
    static constexpr const char* DEFAULT_SHADER_CONF_FILENAME = "shaders.conf";

    /* Constant used in shader files loading?*/
    static const unsigned int MAX_SIZE_SHADER_FILENAME = 15;
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
        //Matrix for transformations
        GLuint _uMVPMatrix;
        GLuint _uMVMatrix;
        GLuint _uNormalMatrix;
        //for Blinn-Phong, properties of the material
        GLuint _uColour, _uKd, _uKs, _uShininess;
        //light properties (light position is in View Space coordinates)
        /* Only the ID of the property is stored, not the light itself
         * which will change depending on the camera.
         */
        //todo: add support for multiple lights, including directional light.
        GLuint _uAmbiantLightData;
        GLuint _sPointLightData_vs, _sDirLightData_vs;

    private:
        void loadProgramme(const glimac::FilePath& appPathDir, const ShaderCouple& couple);
        void getAllAttrLoc();
    private:
        void initSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple);
    public:
        ShaderSender() = default;
        ShaderSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple);



        ///brief; Send ModelView, ModevViewPorjection (From Projection and ModelView), and Normal matrices to shaders

        void sendUniAttribMatrix4(const GLuint uniTarget, const UniformMatrix &M) const;
        void sendUniAttribVec3(const GLuint uniTarget, const glm::vec3 &vec) const;
        void sendUniAttribFloat(const GLuint uniTarget, const GLfloat value) const;

        void sendStorageBlockBuffer(const GLuint blockTarget, const GLuint bindTarget) const;

        void sendMVPNMatrices(const UniformMatrix& MVMatrix, const UniformMatrix& ProjMatrix, const UniformMatrix& NormalMatrix) const;
        void sendMaterial(const Material& material);
        void sendLights() const;

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

}

#endif //WORLD_IMAKER_SHADERSENDER_HPP
