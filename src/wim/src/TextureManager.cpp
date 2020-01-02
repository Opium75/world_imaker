//
// Created by piptouque on 28/12/2019.
//

#include "../include/wim/TextureManager.hpp"


#include <string>


namespace wim
{
    void CubeMap::loadFileNames(std::ifstream &conf)
    {
        if (!conf.is_open())
        {
            throw Exception(ExceptCode::NULL_POINTER, 1, "Trying to access empty stream. Is file properly loaded ?");
        }
        std::string buffer;
        for( SizeInt i=0; i<NB_FACES_CUBE; ++i )
        {
            conf >> buffer;
            _fileNames.push_back(buffer);
        }
    }

    void CubeMap::loadImages(const glimac::FilePath &appPathDir)
    {
        std::string texturePath;
               
        for (SizeInt i = 0; i < NB_FACES_CUBE; ++i)
        {
            texturePath = std::string(appPathDir) + SEP + DEFAULT_RESOURCES_DIR + SEP + DEFAULT_TEXTURE_DIR + SEP +
                _fileNames.at(i);
            _faces.push_back(glimac::ImageManager::loadImage(texturePath));
            if (_faces.back() == nullptr)
            {
                throw Exception(ExceptCode::NULL_POINTER, 1, "Could not load texture at path: " + texturePath);
            }
        }
    }

        void CubeMap::loadFaces(const glimac::FilePath &appDirPath, std::ifstream &conf)
        {
            this->loadFileNames(conf);
            this->loadImages(appDirPath);
        }

    TextureManager::TextureManager(const glimac::FilePath& appPath):
            _appPathDir(appPath.dirPath().dirPath())
    {
        this->readConfig();
    }

        void TextureManager::readConfig() {
            std::ifstream conf;
            std::string confPath = std::string(_appPathDir) + SEP + DEFAULT_RESOURCES_DIR + SEP + DEFAULT_TEXTURE_DIR + SEP + DEFAULT_TEXTURE_CONF_FILENAME;
            conf.open(confPath);
            if (!conf.is_open())
                throw Exception(ExceptCode::NULL_POINTER, 1, std::string("Could not open file at path: ") + confPath);
            //get expected number of textures
            SizeInt n;
            conf >> n;
            //ending line
            //ignoreUntilEndOfLine(conf);
            //fill vector of texture names
            _cubeMaps.reserve(n);
            //do n times
            for (SizeInt i = 0; i < n; ++i) {
                if (conf.fail())
                    throw Exception(ExceptCode::END_OF_FILE, 1,
                                    std::string("Fewer textures than expected: expected ")
                                    + std::to_string(n) + std::string(", found ") + std::to_string(i)
                    );
                _cubeMaps.push_back(CubeMap(_appPathDir, conf));
            }
            conf.close();
        }

    CubeMap::CubeMap(const glimac::FilePath& appDirPath, std::ifstream& conf) :
            _fileNames(),
            _faces()
    {
        _fileNames.reserve(NB_FACES_CUBE);
        _faces.reserve(NB_FACES_CUBE);
        this->loadFaces(appDirPath, conf);
    }

    const ImagePtr& CubeMap::face(const SizeInt index) const {return _faces.at(index);}
    GLsizei CubeMap::getWidth(const SizeInt index) const
    {
        return this->face(index)->getWidth();
    }
    GLsizei CubeMap::getHeight(const SizeInt index) const
    {
        return this->face(index)->getHeight();
    }
    glm::vec4* CubeMap::getPixels(const SizeInt index) const
    {
        return this->face(index)->getPixels();
    }

    SizeInt CubeMap::getNumberFaces() const {return _faces.size();}
}