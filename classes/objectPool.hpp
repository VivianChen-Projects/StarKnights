#pragma once

#include "objectFactory.h"
#include "string"
#include "constantMoveComp.hpp"
#include "hitByHammerComp.hpp"
#include "soundManager.hpp"
using namespace std;

//pool doesnt initialize/change anything about the objects

class objectPool
{
    private:
        vector<GD_ModularObject*> pool;

    public:
        objectPool(string objName, string textureName, int poolSize, bool isAnimated);

        GD_ModularObject* requestFromPool();
        void releaseIntoPool(GD_ModularObject* object); 
        int getAvailableSize();

        void givePoolConstantMoveComp(string direction, float speed);
        void setUpFireballPool(GD_ModularObject* player, GD_ModularObject* hammer, SoundManager* soundManager);

        //add funcs to give all objs in pool a specific component
};