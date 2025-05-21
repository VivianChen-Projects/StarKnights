#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "iostream"
#include "GD_Trn.h"
#include "objectPool.hpp"
#include "soundManager.hpp"
#include "vector"

using namespace std;
using namespace sf;

//handles collecting a hammer power up item
//needs the hammer item to be in a pool
class HammerPowerComp: public GD_Component
{
    private:
        SoundManager* soundManager;
        objectPool* hammerPool;
        vector<GD_ModularObject*>* gameObjectsVector;
        bool bgmToggle, allowbgm, firstToggle = true;

    public:
        HammerPowerComp(GD_ModularObject* player, SoundManager* SoundManager, objectPool* HammerPool, vector<GD_ModularObject*>* GameObjectsVector, bool allowBGM):GD_Component("HammerPowerComp")
        {
            attachOwner(player);
            soundManager = SoundManager;
            hammerPool = HammerPool;
            gameObjectsVector = GameObjectsVector;
            allowbgm = allowBGM;
        }

        void perform() override;
};