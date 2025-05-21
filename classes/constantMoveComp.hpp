#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "iostream"

using namespace std;

//moves in a constant direction, cant change

class ConstantMoveComp: public GD_Component
{
    public:
        enum Direction{up, down, left, right};
        ConstantMoveComp(GD_ModularObject* owner, string name, Direction Direction, float movementSpeed):GD_Component(name)
        {
            attachOwner(owner);
            direction = Direction;
            speed = movementSpeed;
        }
    
    private:
        Direction direction;
        float speed;
        
        void perform() override;
};