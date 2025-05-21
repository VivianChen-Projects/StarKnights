#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "constantMoveComp.hpp"
#include "iostream"

using namespace std;

//moves 1 platform block back and forth

class MovingPlatComp: public GD_Component
{
    public:
        enum Direction{up, down, left, right};
        MovingPlatComp(GD_ModularObject* owner, float movementSpeed, Direction StartDirection, int distanceInTiles, GD_ModularObject* Player):GD_Component("MovingPlatComp")
        {
            attachOwner(owner);
            speed = movementSpeed;
            startDirection = StartDirection;
            player = Player;
            distance = distanceInTiles;
            start = true;
            cooldown = 60;
        }
    
    private:
        float speed;
        int distance;
        float startingCoord;
        Direction startDirection;
        GD_ModularObject* player;
        GD_Component* leftComp;
        GD_Component* rightComp;
        GD_Component* upComp;
        GD_Component* downComp;
        bool start;
        int cooldown;
        
        void perform() override;
        void reverseDirection();
};