#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "soundManager.hpp"

using namespace sf;
using namespace std;

//sfx comp for the player
class SfxComp: public GD_Component
{
    private:
        SoundManager* soundManager;
        bool walkStartToggle, walkEndToggle, walkLock, jumpToggle, jumpLock = false;
        int jumpCooldown = 0;

    public:
        SfxComp(GD_ModularObject* owner, SoundManager* SoundManager):GD_Component("SfxComp")
        {
            attachOwner(owner);
            soundManager = SoundManager;
        }

        void perform() override;
};