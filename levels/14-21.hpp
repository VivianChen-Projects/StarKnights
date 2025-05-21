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

class Stage1421: public Scene
{
    private:
        PlatSpawnerManager platSpawnerManager;
        SoundManager soundManager;
        bool introToggle = true;
        int introDuration = 0, boxCooldow = 0;
        Font light, regular, bold;
        vector<optional<Text>> texts;
        vector<optional<Text>> objective;
        optional<GD_ModularObject*> Box1, Box2;

    public:
        Stage1421()
        {
            if(!light.openFromFile("assets/DIN 2014 light.otf"));
                cout << "";
            if(!regular.openFromFile("assets/DIN 2014 regular.otf"));
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