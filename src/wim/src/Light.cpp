//
// Created by piptouque on 23/12/2019.
//

#include "../include/wim/Light.hpp"

namespace wim
{
    LightManager::LightManager() :
        _listPoint(), _listDir(), _ambiant(), _ssboP(), _ssboD()
    {
        //Enough space for lights
        _listPoint.reserve(MAX_NB_EACH_LIGHTS);
        _listDir.reserve(MAX_NB_EACH_LIGHTS);
        /* */
        glGenBuffers(1, &_ssboP);
        glGenBuffers(1, &_ssboD);
        /* */
        buildSSBO();
    };

    LightManager::~LightManager()
    {
        glDeleteBuffers(1, &_ssboP);
        glDeleteBuffers(1, &_ssboD);
    };

    void LightManager::buildSSBO() const
    {

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssboP);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
                     _listPoint.size()*sizeof(PointLightData),
                     _listPoint.data(),
                     GL_DYNAMIC_COPY
        );
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssboD);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
                     _listDir.size()*sizeof(DirectionalLightData),
                     _listDir.data(),
                     GL_DYNAMIC_COPY
        );
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void LightManager::updateSSBO() const
    {
        GLvoid *bufferPtr;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssboP);
            bufferPtr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
                std::memcpy(bufferPtr, _listPoint.data(), _listPoint.size()*sizeof(PointLightData));
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        //todo: Check if unbinding here is a mistake.
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssboD);
            bufferPtr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
                std::memcpy(bufferPtr, _listDir.data(), _listDir.size()*sizeof(DirectionalLightData));
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }


    void update()
    {

        //todo: only update SSBOs when there is a change in lights.
    }


}