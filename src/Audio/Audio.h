#pragma once

#include <SFML/Audio.hpp>
#include "IGameObject.h"

#define ASSETS_AUDIO_PATH "assets/audio/Kai_Engel_-_09_-_Homeroad.wav"

class Audio : public Engine::IGameObject
{
    private:
        sf::Music m_music;

    public:
        void start();
};