#pragma once 

#include "constantMoveComp.hpp"
#include "Definitions.hpp"
#include "objectFactory.h"
#include "GD_ModularObject.h"

using namespace std;
using namespace sf;

//handles all vertical platform spawners
//ONLY VERTICAL MOVING, 2 TILE WIDE PLATFORMS

struct Spawner;

class PlatSpawnerManager
{
    private:
        vector<Spawner> spawners;
        vector<GD_ModularObject*>* scenePlatforms;
        ObjectFactory objectFactory;
        GD_ModularObject* Player;

    public:
        enum Direction{up, down};
        ~PlatSpawnerManager();
        void reset();
        void giveScenePlatformsVector(vector<GD_ModularObject*>* Platforms);
        void giveScenePlayer(GD_ModularObject* player);
        PlatSpawnerManager* makePlatSpawnerManager();
        void makeNewSpawner(float Speed, int TilesInBewteenPlats, int Distance, Direction Direction, int startXinTiles, int startYinTiles);
        void update(); //handles moving the player when touching one of the platforms 
                    //and to tp the platforms when reaching the target distance
};

struct Spawner
{
    vector<GD_ModularObject*> Plats;
    PlatSpawnerManager::Direction direction;
    int distance;
    int startX;
    int startY;
    float speed;
};
typedef struct Spawner Spawner;