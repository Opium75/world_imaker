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

        ShaderManager(const glimac::FilePath& appPath) : _appPathDir(glimac::FilePath(appPath).dirPath().dirPath())
        {
           this->readConfig();
           this->_buffers.init(_listSender);
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

        inline void updateMVPNMatricesCurrent(const UniformMatrix& MVMatrix, const UniformMatrix& ProjMatrix) const
        {
            this->_buffers.updateMatrices(MVMatrix, ProjMatrix);
        }
        inline void updateLightsCurrent(const AmbiantLightData& ambiant) const
        {
            this->_buffers.updateAmbiantLight(ambiant);
        }
        inline void updateMaterialCurrent(const Material& material ) const
        {
            this->_buffers.updateMaterial(material);
        }

    };


}

#endif //WORLD_IMAKER_SHADERMANAGER_HPP
