//
// Created by piptouque on 28/12/2019.
//

#ifndef WORLD_IMAKER_TEXTUREMANAGER_HPP
#define WORLD_IMAKER_TEXTUREMANAGER_HPP

#pragma once

#include "CommonPath.hpp"
#include "CommonDisplay.hpp"

#include <glimac/Image.hpp>
#include <vector>
#include <memory>

namespace wim
{

    typedef glimac::Image* ImagePtr;

    static constexpr const SizeInt NB_FACES_CUBE = 6;
    class CubeMap
    {
    public:
        typedef std::vector<ImagePtr> FacesPtr;
        typedef std::vector<std::string> FacesFileNames;
    private:
        FacesFileNames _fileNames;
        FacesPtr _faces;
    public:
        CubeMap(const glimac::FilePath& appDirPath, std::ifstream& conf);
        ~CubeMap() = default;

        const ImagePtr& face(const SizeInt index) const;
        GLsizei getWidth(const SizeInt index) const;
        GLsizei getHeight(const SizeInt index) const;
        glm::vec4* getPixels(const SizeInt index) const;

        SizeInt getNumberFaces() const;

    private:
        void loadFaces(const glimac::FilePath& appPathDir, std::ifstream& conf);
        void loadFileNames(std::ifstream &conf);
        void loadImages(const glimac::FilePath &appPathDir);
    };


    typedef std::vector<CubeMap> ListCubeMap;

    class TextureManager
    {
    public:
    private:
        glimac::FilePath _appPathDir;
        ListCubeMap _cubeMaps;
    public:
        TextureManager(const glimac::FilePath& appPath);

        inline const ListCubeMap& getCubeMaps() const {return _cubeMaps;}

    private:
        void readConfig();
    };

    typedef std::unique_ptr<TextureManager> TextureManagerPtr;
}

#endif //WORLD_IMAKER_TEXTUREMANAGER_HPP
