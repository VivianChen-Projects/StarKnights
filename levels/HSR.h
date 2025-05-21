#pragma once

#include "../classes/scene.hpp"
#include "../classes/physicsComp.hpp"
#include "../classes/ladderComp.h"
#include "../classes/playerMoveComp.hpp"
#include "../classes/enemyComp.h"
#include "../classes/spriteComp.h"
#include "../classes/constantMoveComp.hpp"
#include "../classes/movingPlatComp.hpp"
#include "../classes/platSpawnerManager.hpp"
#include "../classes/enemyDamageComp.hpp"
#include "../classes/soundManager.hpp"
#include "../classes/sfxComp.hpp"
#include "../classes/orbitComp.hpp"

using namespace std;
using namespace sf;

class HSR: public Scene
{
    private:
        PlatSpawnerManager platSpawnerManager;
        SoundManager soundManager;
        bool introToggle = true;
        int introDuration = 0, boxCooldow = 0;
        Font light, bold;
        vector<optional<Text>> texts;
        vector<optional<Text>> objective;

        int barrelCooldown = 50;
        int barrelSpawnTimer = 0;
        int springCooldown = 200;
        int springSpawnTimer = 0;


    public:
    HSR()
        {
            if(!light.openFromFile("assets/DIN 2014 light.otf"));
                cout << "";
            if(!bold.openFromFile("assets/DIN-2014_Bold.otf"));
                cout << "";
        }
        void load() override;
        void unLoad() override;
        int update() override;
        void draw(RenderWindow* window) override;

        void intro();
};