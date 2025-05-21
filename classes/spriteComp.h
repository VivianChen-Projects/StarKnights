#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"

using namespace sf;
using namespace std;

//handles sprite animations 
class SpriteComp: public GD_Component
{
    private:
        int x;
        int y;
        int w;
        int h;
        float time;
        float cooldown;
        Clock clock;
        int counter;
        string prevState;
        string approachingLadder;
        bool killed;
        bool setStart;
    public:
        SpriteComp(GD_ModularObject* owner):GD_Component("SpriteComp")
        {
            killed = false;
            cooldown = 0;
            setStart = false;
            time = 0;
            counter = 0;
            attachOwner(owner);
        }

        void perform() override;
};