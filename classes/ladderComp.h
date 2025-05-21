#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "iostream"

using namespace std;
using namespace sf;

//only handles ladder collions and movement

class LadderComp: public GD_Component
{

    public:
        LadderComp(GD_ModularObject* owner):GD_Component("LadderComp")
        {
            attachOwner(owner);
        }

        void perform() override;
};