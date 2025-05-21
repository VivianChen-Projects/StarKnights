#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "iostream"

using namespace std;

//handles basic collision events 

class PhysicsComp: public GD_Component
{
    private:
        int savedX;
        int savedY;
        int ogJumpY;
        int floatTimer;
        bool floating = false;

    public:
        PhysicsComp(GD_ModularObject* owner):GD_Component("PhysicsComp")
        {
            attachOwner(owner);
        }

        void perform() override;
};