//
// Created by piptouque on 28/12/2019.
//

#include "../include/wim/TextureManager.hpp"

#include <string>
#include <limits>


namespace wim {

    void CubeMap::loadFileName(std::ifstream &conf)
    {
        if (!conf.is_open()) {
            throw Exception(ExceptCode::NULL_POINTER, 1, "Trying to access empty stream. Is file properly loaded ?");
        }
        std::string buffer;
        conf >> buffer;
        _fileNames.push_back(buffer);

    }

    void CubeMap::loadImage(const glimac::FilePath &appPathDir)
    {
        std::string texturePath = std::string(appPathDir) + SEP + DEFAULT_TEXTURE_DIR + SEP + _fileNames.back();
       _faces.push_back(glimac::ImageManager::loadImage(texturePath));
        if( _faces.back() == nullptr )
        {
            throw Exception(ExceptCode::NULL_POINTER, 1, "Could not load texture at path: " + texturePath);
        }
    }

    void CubeMap::loadFace(const glimac::FilePath &appDirPath, std::ifstream &conf)
    {
        this->loadFileName(conf);
        this->loadImage(appDirPath);
    }

    void CubeMap::loadFaces(const glimac::FilePath &apppDirPath, std::ifstream &conf)
    {
        for( SizeInt i=0; i<NB_FACES_CUBE; ++i )
        {
            this->loadFace(apppDirPath, conf);
        }
        conf.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void TextureManager::readConfig() {
        std::ifstream conf;
        std::string confPath = std::string(_appPathDir) + SEP + DEFAULT_TEXTURE_DIR + SEP + DEFAULT_TEXTURE_CONF_FILENAME;
        conf.open(confPath);
        if (!conf.is_open())
            throw Exception(ExceptCode::NULL_POINTER, 1, std::string("Could not open file at path: ") + confPath);
        //get expected number of textures
        SizeInt n;
        conf >> n;
        //ending line
        conf.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //fill vector of texture names
        _cubeMaps.reserve(n);
        //do n times
        for (SizeInt i = 0; i < n; ++i) {
            if (conf.eof())
                throw Exception(ExceptCode::END_OF_FILE, 1,
                                std::string("Fewer textures than expected: expected ")
                                + std::to_string(n) + std::string(", found ") + std::to_string(i)
                );
            _cubeMaps.push_back(CubeMap(_appPathDir, conf));
        }
        conf.close();
    }

}