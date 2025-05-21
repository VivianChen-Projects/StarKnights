#include "ladderComp.h"

//only handles ladder collions and movement
void LadderComp::perform()
{
    GD_ModularObject* owner = getOwner();
    
    if(Keyboard::isKeyPressed(Keyboard::Scancode::W) && owner->collisions.climbing)
        owner->move(0, PLAYERMOVEMENTSPEED);

    if(Keyboard::isKeyPressed(Keyboard::Scancode::S) && owner->collisions.climbing)
        owner->move(0, -PLAYERMOVEMENTSPEED);

    //ends climb when touching ground/bottom of ladder
    if(owner->collisions.climbing && owner->collisions.floor) 
    {
        owner->collisions.climbing = false;
        owner->enableComponent("PlayerMoveComp");
        owner->move(0,3);
    }

    //ends climb when touching top of platform above ladder
    if(owner->collisions.climbing && owner->collisions.tileAboveLadder)
    {
        owner->collisions.climbing = false;
        owner->enableComponent("PlayerMoveComp");
        owner->move(0,3);
    }

    //snaps player onto bottom of ladder
    if(owner->collisions.startClimbBot)
    {
        owner->disableComponent("PlayerMoveComp");
        owner->getSprite()->setPosition({owner->collisions.collidingLadder->getSprite()->getPosition().x, owner->getSprite()->getPosition().y - 5});
        owner->collisions.startClimbBot = false;
        owner->collisions.climbing = true;
        owner->collisions.floor = false;
    }

    //snaps player onto top of ladder
    if(owner->collisions.startClimbTop)
    {
        owner->disableComponent("PlayerMoveComp");
        owner->getSprite()->setPosition({owner->collisions.collidingLadder->getSprite()->getPosition().x, owner->collisions.collidingLadder->getSprite()->getPosition().y});
        owner->collisions.startClimbTop = false;
        owner->collisions.climbing = true;
    }
}