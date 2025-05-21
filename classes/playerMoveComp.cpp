#include "playerMoveComp.hpp"

//gets player input for mario
void PlayerMoveComp::perform()
{
    if(!getEnabled())
        return;

    GD_ModularObject* owner = getOwner();

    if(Keyboard::isKeyPressed(Keyboard::Scancode::D)){
        owner->collisions.walkRight = true;
        owner->move(PLAYERMOVEMENTSPEED, 0);
        owner->setFaceDirection(RIGHT);
    }

    if(Keyboard::isKeyPressed(Keyboard::Scancode::A)){
        owner->collisions.walkLeft = true;
        owner->move(-PLAYERMOVEMENTSPEED, 0);
        owner->setFaceDirection(LEFT);
    }

    jumpExt--;
    if(jumpExt >= 0)
        owner->collisions.jumping = true;
    if(Keyboard::isKeyPressed(Keyboard::Scancode::Space) && owner->collisions.floor)
    {
        owner->collisions.jumping = true;
        jumpExt = 7;
    }

    if(Keyboard::isKeyPressed(Keyboard::Scancode::W) && owner->collisions.ladder && !owner->collisions.jumping && owner->collisions.floor && !owner->collisions.climbing)
        owner->collisions.startClimbBot = true;

    if(Keyboard::isKeyPressed(Keyboard::Scancode::S) && owner->collisions.tileAboveLadder && !owner->collisions.climbing)
        owner->collisions.startClimbTop = true;
    
    //if player is out of bounds, kills them
    if(owner->getSprite()->getPosition().y >= TILESCALE*34)
        owner->setHP(0);
}