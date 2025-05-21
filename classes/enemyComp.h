#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "iostream"
#include "GD_Trn.h"

using namespace std;
using namespace sf;


class EnemyComp: public GD_Component
{
    private:
        float time;
        Clock clock;
        int springJumpCooldown = 0;
        bool springJumpToggle = false;
    public:
        EnemyComp(GD_ModularObject* owner):GD_Component("EnemyComp")
        {
            time = 0;
            attachOwner(owner);
        }

        void perform() override;
};