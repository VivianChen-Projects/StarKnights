#include "soundManager.hpp"

//keeps all the sounds and music

void SoundManager::addSFX(string fileAdress, string newName)
{
    Music bgm(fileAdress);
    bgm.setVolume(SoundVolume+.0f);
    bgm.setLooping(false);

    MUSICS temp;
    temp.music = move(bgm);
    temp.name = newName;

    sfxVector.push_back(move(temp));
}

void SoundManager::playSFX(string name, bool loop)
{
    for(int i = 0; i < sfxVector.size(); i++)
        if(sfxVector.at(i).name == name && sfxVector.at(i).music.has_value())
        {
            //reset sfx
            sfxVector.at(i).music.value().stop();

            if(loop)
                sfxVector.at(i).music.value().setLooping(loop);

            sfxVector.at(i).music.value().play();
            break;
        }
}

void SoundManager::stopSFXLoop(string name)
{
    for(int i = 0; i < sfxVector.size(); i++)
        if(sfxVector.at(i).name == name)
        {
            sfxVector.at(i).music.value().stop();
            sfxVector.at(i).music.value().setLooping(false);
            break;
        }
}

void SoundManager::addBGM(string fileAdress, string newName)
{
    Music bgm(fileAdress);
    bgm.setVolume(MusicVolume+.0f);
    bgm.setLooping(true);

    MUSICS temp;
    temp.music = move(bgm);
    temp.name = newName;

    bgmVector.push_back(move(temp));
}

void SoundManager::playBGM(string name)
{
    for(int i = 0; i < bgmVector.size(); i++)
        if(bgmVector.at(i).name == name && bgmVector.at(i).music.has_value())
        {
            bgmVector.at(i).music.value().play();
            break;
        }
}

void SoundManager::stopBGM(string name)
{
    for(int i = 0; i < bgmVector.size(); i++)
        if(bgmVector.at(i).name == name)
        {
            bgmVector.at(i).music.value().stop();
            break;
        }
}   

void SoundManager::reset()
{
    sfxVector.clear();
    bgmVector.clear();
}