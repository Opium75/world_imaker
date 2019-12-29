//
// Created by piptouque on 18/12/2019.
//

#ifndef WORLD_IMAKER_SHADERSENDER_HPP
#define WORLD_IMAKER_SHADERSENDER_HPP

#pragma once


#include <glimac/Programme.hpp>


#include "CommunPath.hpp"
#include "Types.hpp"
#include "Exception.hpp"
#include "Material.hpp"

namespace wim
{;

    static constexpr const char* STORAGE_POSLIGHT_NAME = "sPosLight_vs";
    static constexpr const char* STORAGE_DIRLIGHT_NAME = "sDirLight_vs";

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

    private:
        void loadProgramme(const glimac::FilePath& appPathDir, const ShaderCouple& couple);
    private:
        void initSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple);
    public:
       // ShaderSender() = default;
        ShaderSender(const glimac::FilePath& appPathDir, const ShaderCouple& couple);


        inline void useProgramme() const {
            _programme.use();
            std::cout << "Using programme #" << _programme.getGLId() << std::endl;
        }

        inline const glimac::Programme& programme() const {return _programme;}
        inline glimac::Programme& programme() {return _programme;}

        inline const ShaderCouple& couple() const { return _couple;}
        inline ShaderCouple& couple() { return _couple;}


        friend std::ostream& operator<<(std::ostream& out , const ShaderSender& sender)
        {
            out << sender._programme.getGLId() << " | " << sender._couple;
            return out;
        }

    };

    //typedef for convenience
    typedef std::vector<ShaderSender> ListSender;

}

#endif //WORLD_IMAKER_SHADERSENDER_HPP
