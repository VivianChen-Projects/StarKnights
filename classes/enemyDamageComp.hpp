#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"

using namespace std;
using namespace sf;

//only for the player
//makes player take damage when hitting an enemy

class EnemyDamageComp: public GD_Component
{
    private:
        int invulTimer = 0;

    public:
        EnemyDamageComp(GD_ModularObject* owner):GD_Component("EnemyDamageComp")
        {
            attachOwner(owner);
        }

        void perform() override;
};