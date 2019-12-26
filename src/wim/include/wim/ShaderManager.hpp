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
#include "Exception.hpp"
#include "BufferManager.hpp"
#include "ShaderSender.hpp"

namespace wim
{
    class ShaderManager
    {
    private:
        glimac::FilePath _appPathDir;
        ListSender  _listSender;
        SizeInt _currentIndex;
        BufferManager _buffers;
    public:
        ShaderManager() = default;

        ShaderManager(const glimac::FilePath& appPath) :
            _appPathDir(glimac::FilePath(appPath).dirPath().dirPath()),
            _currentIndex(0)
        {
           this->readConfig();
            std::cout << *this << std::endl;
           this->setCurrentProgramme(_currentIndex);
           this->_buffers.bindShaders(_listSender);
           std::cout << *this << std::endl;
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

        inline const ShaderSender& currentSender() const {return _listSender.at(_currentIndex);}

        inline void updateMVPNMatrices(const UniformMatrix& MVMatrix, const UniformMatrix& ProjMatrix) const
        {
            this->_buffers.updateMatrices(MVMatrix, ProjMatrix);
        }
        inline void updateLights(const LightManager& lights) const
        {
            this->_buffers.updateLights(lights);
        }
        inline void updateMaterial(const Material& material ) const
        {
            this->_buffers.updateMaterial(material);
        }

        friend std::ostream& operator<<(std::ostream& out, const ShaderManager& shaders)
        {
            for( const auto& shader : shaders._listSender)
            {
                out << shader << std::endl;
            }
            return out;
        }


    };


}

#endif //WORLD_IMAKER_SHADERMANAGER_HPP
