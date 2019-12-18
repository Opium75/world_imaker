//
// Created by piptouque on 18/12/2019.
//

#ifndef WORLD_IMAKER_SHADERMANAGER_HPP
#define WORLD_IMAKER_SHADERMANAGER_HPP

#pragma once

#include <vector>

#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include "ShaderLoader.hpp"


namespace wim
{
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
    //LGIHT
    constexpr static const char* UNI_LIGHTPOS_NAME = "uLightPos_vs";
    constexpr static const char* UNI_LIGHTINTENSITY_NAME = "uLightPos_vs";

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

        inline const glimac::Program& getProgramme() const {return _programme;}

        inline glimac::Program& getProgramme() {return _programme;}

        inline void useShaders() const {_programme.use();}

        friend std::ostream& operator<<(std::ostream& stream, const ShaderManager& manager)
        {
            stream << manager._couple << std::endl;
            return stream;
        }

    private:
       void loadProgramme(const glimac::FilePath& appPathDir, const ShaderCouple& couple);

        void loadUniAttrLoc();


        void loadProgramme(const glimac::FilePath &appPathDir, const ShaderCouple &couple);
    };

}

#endif //WORLD_IMAKER_SHADERMANAGER_HPP
