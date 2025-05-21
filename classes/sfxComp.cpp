#include "sfxComp.hpp"

//sfx comp for the player
void SfxComp::perform()
{
    GD_ModularObject* owner = getOwner();

    if(walkStartToggle && !walkLock && owner->collisions.floor)
    {
        walkStartToggle = false;
        walkLock = true;
        soundManager->playSFX(WALKINGSFX, true);
    }
    if(walkEndToggle || !owner->collisions.floor)
    {
        walkEndToggle = false;
        walkLock = false;
        soundManager->stopSFXLoop(WALKINGSFX);
    }

    jumpCooldown--;
    if(jumpToggle && !jumpLock && jumpCooldown <= 0)
    {
        jumpCooldown = 10;
        jumpToggle = false;
        jumpLock = true;
        soundManager->playSFX(JUMPSFX, false);
    }    


    //player input getting
    if(owner->getID() == PLAYER)
    {
        if(owner->collisions.walkLeft || owner->collisions.walkRight)
            walkStartToggle = true;
        else if(!owner->collisions.walkLeft && !owner->collisions.walkRight)
            walkEndToggle = true;

        if(owner->collisions.jumping && !jumpLock)
            jumpToggle = true;
        else if(!owner->collisions.jumping && owner->collisions.floor)
            jumpLock = false;
    }
}