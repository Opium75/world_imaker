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


namespace wim
{



<<<<<<< HEAD
=======
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
>>>>>>> ImGui

}

#endif //WORLD_IMAKER_SHADERMANAGER_HPP
