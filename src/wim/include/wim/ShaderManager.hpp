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
#include "Displayable.hpp"
#include "Model.hpp"
#include "PatternManager.hpp"
#include "BufferManager.hpp"
#include "TextureManager.hpp"
#include "ShaderSender.hpp"

namespace wim
{

    class ShaderManager
    {
    private:
        glimac::FilePath _appPathDir;
        ListSender  _listSender;
        SizeInt _currentIndex;
        TextureManagerPtr _textures;
        BufferManagerPtr _buffers;
    public:
        ShaderManager(const glimac::FilePath& appPath, const WindowManagerPtr& windows) :
            _appPathDir(glimac::FilePath(appPath).dirPath().dirPath()),
            _currentIndex(0),
            _textures(std::make_unique<TextureManager>(appPath)),
            _buffers(std::make_unique<BufferManager>(_textures, windows))
        {
           this->readConfig();
           this->setCurrentProgramme(_currentIndex);
           this->bindShaders();
           _buffers->loadCubeMaps(_textures->getCubeMaps());
           Displayable::linkTextures(_buffers->getListITO());
        }
        ~ShaderManager() = default;

        void readConfig();

        inline void setCurrentProgramme(const SizeInt index)
        {
            _listSender.at(index).useProgramme();
            _buffers->localiseUniform(_listSender.at(index));
            _currentIndex = index;
        }

        inline SizeInt getNumberProgrammes() const
        {
            return _listSender.size();
        }
        inline const glimac::Programme& programme(const SizeInt index) const {return _listSender.at(index).programme();}

        inline const ShaderCouple& couple(const SizeInt index) const {return _listSender.at(index).couple();}

        inline const glimac::Programme& currentProgramme() const {return this->programme(_currentIndex);}

        inline const ShaderSender& currentSender() const {return _listSender.at(_currentIndex);}

        inline const BufferManagerPtr& bufferManager() const {return _buffers;}

        inline void bindShaders() const
        {
            _buffers->bindShaders(_listSender);
        }
        inline void updateMVPNMatrices(const UniformMatrix& MVMatrix, const UniformMatrix& ProjMatrix) const
        {
            this->_buffers->updateMatrices(MVMatrix, ProjMatrix);
        }
        inline void updateLights(const LightManager& lights, const UniformMatrix& View) const
        {
            this->_buffers->updateLights(lights, View);
        }
        inline void updateMaterial(const Material& material, const bool isTextured) const
        {
            this->_buffers->updateMaterial(material, isTextured);
        }


        friend std::ostream& operator<<(std::ostream& out, const ShaderManager& shaders)
        {
            for( const auto& shader : shaders._listSender)
            {
                out << shader << std::endl;
            }
            return out;
        }

        inline void drawItem(const Renderable& item, const PatternManager& patterns) const
        {
            patterns.draw(item);
        }
        //todo: this.


    };


}

#endif //WORLD_IMAKER_SHADERMANAGER_HPP
