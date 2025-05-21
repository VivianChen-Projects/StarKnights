#pragma once

#include "SFML/Audio.hpp"
#include "vector"
#include "string"
#include "Definitions.hpp"

using namespace std;
using namespace sf;

struct MUSICS
{
    optional<Music> music;
    string name;
};
typedef struct MUSICS MUSICS;

//keeps all the sounds and music
//the sound class wasnt used cuz it wasnt loading right, so music was used for everything 
class SoundManager
{
    private:
        vector<MUSICS> sfxVector;
        vector<MUSICS> bgmVector;

    public:
        void addSFX(string fileAdress, string newName);
        void playSFX(string name, bool loop);
        void stopSFXLoop(string name);

        void addBGM(string fileAdress, string newName);
        void playBGM(string name);
        void stopBGM(string name);

        void reset();
};