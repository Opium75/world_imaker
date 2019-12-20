//
// Created by piptouque on 17/12/2019.
//

#ifndef WORLD_IMAKER_SHADERMANAGER_HPP
#define WORLD_IMAKER_SHADERMANAGER_HPP

#pragma once

#include <vector>


#include <glimac/FilePath.hpp>
#include <glimac/Programme.hpp>

#include "ShaderSender.hpp"
#include "Exception.hpp"

namespace wim
{
    class ShaderManager
    {
    public:
        //typedef for convenience
        typedef std::vector<ShaderSender> ListSender;
    private:
        glimac::FilePath _appPathDir;
        ListSender  _listSender;
    public:
        ShaderManager() = default;

        ShaderManager(const glimac::FilePath& appPath) : _appPathDir(glimac::FilePath(appPath).dirPath().dirPath())
        {
           this->readConfig();
        }
        ~ShaderManager() = default;

        void readConfig();


        inline void useProgramme(const size_t index) const { _listSender.at(index).useProgramme();}

        inline glimac::Programme& programme(const size_t index) {return _listSender.at(index).getProgramme();}
        inline const glimac::Programme& programme(const size_t index) const {return _listSender.at(index).getProgramme();}

        inline ShaderCouple& couple(const size_t index) {return _listSender.at(index).couple();}
        inline const ShaderCouple& couple(const size_t index) const {return _listSender.at(index).couple();}



       /* friend std::ostream& operator<<(std::ostream& stream, const ListCouple& vecShaderCouple)
        {
            for(const auto& couple : vecShaderCouple)
            {
                stream << couple << std::endl;
            }

            return stream;
        }
        */

    };


}

#endif //WORLD_IMAKER_SHADERMANAGER_HPP
