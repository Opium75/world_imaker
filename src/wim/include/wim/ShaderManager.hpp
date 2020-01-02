//
// Created by piptouque on 17/12/2019.
//

#ifndef WORLD_IMAKER_SHADERMANAGER_HPP
#define WORLD_IMAKER_SHADERMANAGER_HPP

#pragma once

#include <vector>
#include <memory>

#include <glimac/FilePath.hpp>
#include <glimac/Programme.hpp>

#include "Types.hpp"
#include "Exception.hpp"

#include "ShaderSender.hpp"

namespace wim
{

    class ShaderManager
    {
    private:
        glimac::FilePath _appPathDir;
        ListSender  _listSender;
        SizeInt _currentIndex;
    public:
        ShaderManager(const glimac::FilePath& appPath);
        ~ShaderManager() = default;

        void readConfig();

        void useProgramme(const SizeInt index);

        inline SizeInt getNumberProgrammes() const
        {
            return _listSender.size();
        }
        inline const glimac::Programme& programme(const SizeInt index) const {return _listSender.at(index).programme();}
        inline const ShaderCouple& couple(const SizeInt index) const {return _listSender.at(index).couple();}
        inline const glimac::Programme& currentProgramme() const {return this->programme(_currentIndex);}
        inline const ShaderSender& currentSender() const {return _listSender.at(_currentIndex);}
        inline const ListSender& listSender() const {return _listSender;}

        friend std::ostream& operator<<(std::ostream& out, const ShaderManager& shaders)
        {
            for( const auto& shader : shaders._listSender)
            {
                out << shader << std::endl;
            }
            return out;
        }


    };

    typedef std::unique_ptr<ShaderManager> ShaderManagerPtr;
}

#endif //WORLD_IMAKER_SHADERMANAGER_HPP
