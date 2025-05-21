#pragma once

class GD_Component;

#include "GD_2DBlockObject.h"
#include "GD_Component.h"
#include <string>

using namespace std;
class GD_ModularObject;

//*insert that one toy story meme*
//"Bools... Bools everywhere!"
struct Collisions
{
        bool floor;
        bool wallRight;
        bool wallLeft;
        bool ceiling;
        bool player;
        bool enemy;
        bool ladder;
        bool climbing;
        bool jumping;
        bool groundClip;
        bool tileAboveLadder;
        bool startClimbTop;
        bool startClimbBot;
        bool platformEnd;
        bool walkLeft;
        bool walkRight;
        bool smash;
        int hammerDuration = 0;
        GD_ModularObject* collidingLadder;
        GD_ModularObject* collidingPlatform;
        GD_ModularObject* collidingHammerItem;
};
typedef struct Collisions Collisions;

//most additions is for collision tracking 
//hp and death status too
//2nd constructor is if the sprite is animated 
class GD_ModularObject: public GD_2DBlockObject{
        private:
                vector<GD_Component*> componentList;
                bool IsVisible;
                bool canCollide;
                int hp;
                bool isDead, returnToPool = false;

        public:
                GD_ModularObject(std::string objName, std::string textureName);
                GD_ModularObject(std::string objName, std::string textureName, int xV, int yV);
                ~GD_ModularObject();
                void attachComponent(GD_Component* component);
                void disableComponent(string compName);
                void enableComponent(string compName);
                void disableAllComps();
                void enableAllComps();
                GD_Component* getComponent(std::string componentName);
                vector<GD_Component*> getComponentList();
                void update() override;

                bool isVisible();
                void toggleVisibility();

                Collisions collisions;

                void setHP(int newHP);
                int getHP();

                void setHeight(int newHeight);
                void setWidth(int newWidth);

                void setDead(bool isDead);
                bool getDeathStatus();

                void setReturnToPool(bool Bool);
                bool getReturnToPool();
};
