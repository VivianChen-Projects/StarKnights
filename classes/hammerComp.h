#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "iostream"
#include "GD_Trn.h"

using namespace std;
using namespace sf;

//handles mario's hammer
//moves hammer along with mario and animates it
class HammerComp: public GD_Component
{
    private:
        float parentX;
        float parentY;
        int x;
        int y;
        int w;
        int h;
        float time;
        Clock clock;
    public:
    HammerComp(GD_ModularObject* owner):GD_Component("EnemyComp")
        {
            parentX = 0;
            parentY = 0;
            x = 0;
            y = 0;
            attachOwner(owner);
        }

        void perform() override;
};