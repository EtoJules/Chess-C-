#include "Audio.h"

void Audio::start() 
{
    if(!m_music.openFromFile(ASSETS_AUDIO_PATH))
    {

    }
    m_music.setLoop(true);
    m_music.play();
}