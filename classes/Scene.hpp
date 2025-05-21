#pragma once 

#include "GD_2DBlockObject.h"
#include "GD_GameObject.h"
#include "objectFactory.h"
#include "objectPool.hpp"
#include "vector"

using namespace std;
using namespace sf;

//theyre put in a struct cuz i thought we might need to pass everything for something, idk
//never really did that 
struct AllObjects
{
    vector<GD_ModularObject*> Platforms;
    vector<GD_ModularObject*> gameObjects;
    vector<GD_ModularObject*> enemies;
    vector<GD_ModularObject*> ladders;
    vector<GD_ModularObject*> aboveLadder;
    vector<GD_ModularObject*> platformEnds;
    GD_ModularObject* player;
    GD_ModularObject* peach;
    GD_ModularObject* hammer;
};
typedef struct AllObjects AllObjects;

class Scene
{
    protected:
        ObjectFactory objectFactory;
        AllObjects allObjects;
        int score;
        float time;
        Clock clock;
        bool winCondition = false;
        
    public:
        Scene();
        virtual void load();
        virtual void unLoad();
        virtual int update(); //check definitions for returns
        virtual void draw(RenderWindow* window); //draw order matters for layering
        void updateAllCollisions(AllObjects allObjects);

    protected:
        bool checkFloorCollison(GD_ModularObject* main, GD_ModularObject* target);
        bool checkWallRightCollison(GD_ModularObject* main, GD_ModularObject* target);
        bool checkWallLeftCollison(GD_ModularObject* main, GD_ModularObject* target);
        bool checkCeilingCollison(GD_ModularObject* main, GD_ModularObject* target);
        bool checkEnemyCollison(GD_ModularObject* main, GD_ModularObject* target);
        bool checkLadderCollison(GD_ModularObject* main, GD_ModularObject* target);
        bool checkGroundClipCollison(GD_ModularObject* main, GD_ModularObject* target);
        bool checkAboveLadderCollision(GD_ModularObject* main, GD_ModularObject* target);
        bool checkPlatformEndCollision(GD_ModularObject* main, GD_ModularObject* target);
};