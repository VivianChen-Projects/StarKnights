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
#include "../classes/objectPool.hpp"
#include "../classes/hammerPowerComp.hpp"
#include "../classes/hitByHammerComp.hpp"

using namespace std;
using namespace sf;

struct BoxSpawner
{
    int spawnInterval;
    int spawnerTimer;
    int spawnX;
    int SpawnY;
    int maxEnemies;
    int minEnemies;
    int hammerSpawnX;
    int hammerSpawnY;
    string startDirection;

    bool isSpawning;
    int enemiesToSpawn;
};
typedef struct BoxSpawner BoxSpawner;

class StageBB10: public Scene
{
    private:
        SoundManager soundManager;

        bool introToggle, phase1, phase2InitToggle, phase3InitToggle, phase4InitToggle = true;
        bool phase2, phase3, phase4 = false;
        int introDuration, boxCooldow = 0;

        Font light, regular, bold;
        GD_ModularObject* amiya;
        vector<optional<Text>> texts;
        vector<optional<Text>> objective;
        vector<optional<GD_ModularObject*>> Boxes, phase1Plats, phase2Plats;
        objectPool fireballPool = objectPool(FIREBALL, "assets/og_Fireball_Sheet.png", 35, true);
        objectPool hammerPool = objectPool(HAMMERITEM, "assets/og_Hammer_Item.png", 5, false);

        BoxSpawner spawner1, spawner2, spawner3, spawner4, spawner5;
        int spawnCooldown = 10*60; //60 per sec
        int spawnTimer = 0;
        int wavesSpawned = 0;
        bool stopSpawning, winstat, p4s1toggle = false;
        int winDelay = 0;

        void intro();
        void checkPhaseTrans();
        void spawnManager();
        void initSpawnerData();
        void updateSpawner(BoxSpawner* spawner);
        void spawnHammerItem(int spawnX, int spawnY);

    public:
        StageBB10()
        {
            if(!light.openFromFile("assets/DIN 2014 light.otf"));
                cout << "";
            if(!regular.openFromFile("assets/DIN 2014 regular.otf"));
                cout << "";
            if(!bold.openFromFile("assets/DIN-2014_Bold.otf"));
                cout << "";

            allObjects.player = objectFactory.makePlayer(8, 13);
            allObjects.player->attachComponent(new SfxComp(allObjects.player, &soundManager));
            allObjects.hammer = objectFactory.makeHammer(allObjects.player);
            allObjects.player->attachComponent(new HammerPowerComp(allObjects.player, &soundManager, &hammerPool, &allObjects.gameObjects, false));

            fireballPool.setUpFireballPool(allObjects.player, allObjects.hammer, &soundManager);
        }
        void load() override;
        void unLoad() override;
        int update() override;
        void draw(RenderWindow* window) override;
};