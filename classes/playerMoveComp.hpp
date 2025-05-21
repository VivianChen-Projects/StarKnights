#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"

using namespace sf;

//gets player input for mario
class PlayerMoveComp: public GD_Component
{
    private:
        int jumpExt = 0;
        
    public:
        PlayerMoveComp(GD_ModularObject* owner):GD_Component("PlayerMoveComp")
        {
            attachOwner(owner);
        }

    void perform() override;
};