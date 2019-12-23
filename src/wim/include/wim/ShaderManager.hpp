//
// Created by piptouque on 17/12/2019.
//

#ifndef WORLD_IMAKER_SHADERMANAGER_HPP
#define WORLD_IMAKER_SHADERMANAGER_HPP

#pragma once

#include <vector>


#include <glimac/FilePath.hpp>
#include <glimac/Programme.hpp>

#include "Types.hpp"
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
        SizeInt _currentIndex;
    public:
        ShaderManager() = default;

        ShaderManager(const glimac::FilePath& appPath) : _appPathDir(glimac::FilePath(appPath).dirPath().dirPath())
        {
           this->readConfig();
        }
        ~ShaderManager() = default;

        void readConfig();


        inline void setCurrentProgramme(const SizeInt index)
        {

            _listSender.at(index).useProgramme();
            _currentIndex = index;
        }

        inline glimac::Programme& programme(const SizeInt index) {return _listSender.at(index).programme();}
        inline const glimac::Programme& programme(const SizeInt index) const {return _listSender.at(index).programme();}

        inline ShaderCouple& couple(const SizeInt index) {return _listSender.at(index).couple();}
        inline const ShaderCouple& couple(const SizeInt index) const {return _listSender.at(index).couple();}

        inline const glimac::Programme& currentProgramme() const {return this->programme(_currentIndex);}

        inline void sendMVPNMatrixCurrent() const {}


    };


}

#endif //WORLD_IMAKER_SHADERMANAGER_HPP
