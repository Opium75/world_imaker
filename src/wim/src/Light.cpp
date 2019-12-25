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
    };

    LightManager::~LightManager()
    {;
    };


    void update()
    {

        //todo: only update SSBOs when there is a change in lights.
    }


}