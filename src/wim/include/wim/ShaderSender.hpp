//
// Created by piptouque on 18/12/2019.
//

#ifndef WORLD_IMAKER_SHADERSENDER_HPP
#define WORLD_IMAKER_SHADERSENDER_HPP

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

#include <glimac/Programme.hpp>
#include <glimac/FilePath.hpp>

#include "Exception.hpp"

namespace wim
{
    /*Names of uniform attributs as they are used in the shaders
     * For now, we will only support one light source. IN POINT LIGHT
     */
    //MATRIX
    constexpr const char* UNI_MVP_NAME = "uMVPMatrix";
    constexpr const char* UNI_MV_NAME = "uMVMatrix";
    constexpr const char* UNI_NORMAL_NAME = "uNormalMatrix";
    //MATERIAL
    constexpr const char* UNI_KD_NAME = "uKd";
    constexpr const char* UNI_KS_NAME = "uKs";
    constexpr const char* UNI_SHININESS_NAME = "uShininess";
    //LIGHT
    constexpr const char* UNI_LIGHTPOS_NAME = "uLightPos_vs";
    constexpr const char* UNI_LIGHTINTENSITY_NAME = "uLightPos_vs";

    /* Path to shaders and config file relative to build directory */
    const std::string DEFAULT_SHADER_DIR("resources/shaders");
    const std::string DEFAULT_SHADER_CONF_FILENAME("shaders.conf");

    /* Constant used in shader files loading?*/
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

    class ShaderSender
    {
    private:
        ShaderCouple _couple;
        glimac::Programme _programme;
        //Matrix for transformations
        GLint _uMVPMatrix;
        GLint _uMVMatrix;
        GLint _uNormalMatrix;
        //for Blinn-Phong, properties of the material
        GLint _uKd, _uKs, _uShininess;
        //light properties (light position is in View Space coordinates)
        /* Only the ID of the property is stored, not the light itself
         * which will change depending on the camera.
         */
        GLint _uLightPos_vs, _uLightIntensity;
    private:
        void loadProgramme(const glimac::FilePath& appPathDir, const ShaderCouple& couple);
        void getAllUniAttrLoc();
    private:
        void initSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple);
    public:
        ShaderSender() = default;
        ShaderSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple) : _couple(couple), _programme()
        {
            //checking for an error in creating the OpenGL programme
            if( _programme.getGLId()  == 0 )
                throw Exception(ExceptCode::INIT_ERROR, 1, "Could not create OpenGL programme.");
            this->initSender(appPathDir, couple);
            //use first programme to begin with ?
            //Nope, will be decided by ShaderManager.
            //this->useProgramme();
        }


        ///brief; Send ModelView, ModevViewPorjection (From Projection and ModelView), and Normal matrices to shaders

        void sendUniAttribMatrix4(const GLint uniTarget, const glm::mat4 &M) const;
        void sendUniAttribVec3(const GLint uniTarget, const glm::vec3 &vec) const;
        void sendUniAttribFloat(const GLint uniTarget, const GLfloat value) const;

        void sendMVPNMatrices(const glm::mat4& MVMatrix, const glm::mat4& ProjMatrix, const glm::mat4& NormalMatrix) const;
        void sendMaterial(const glm::vec3& kD, const glm::vec3& kS, const GLfloat shininess) const;
        void sendLight(const glm::vec3& lightPos_vs, const glm::vec3& lightIntensity) const;

        inline void useProgramme() const {_programme.use();}

        inline const glimac::Programme& getProgramme() const {return _programme;}
        inline glimac::Programme& getProgramme() {return _programme;}

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
