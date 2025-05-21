#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "soundManager.hpp"

using namespace sf;

//only for enemies, kills them when touching mario's hammer
class HitByHammerComp: public GD_Component
{
    private:
        GD_ModularObject* hammer;
        GD_ModularObject* player;
        SoundManager* soundManager;
        
    public:
        HitByHammerComp(GD_ModularObject* owner, GD_ModularObject* Player, GD_ModularObject* Hammer, SoundManager* SoundManager):GD_Component("HitByHammerComp")
        {
            attachOwner(owner);
            hammer = Hammer;
            soundManager = SoundManager;
            player = Player;
        }

    void perform() override;
};