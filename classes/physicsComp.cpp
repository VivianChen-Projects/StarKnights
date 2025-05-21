#include "physicsComp.hpp"

//handles basic collision events 
void PhysicsComp::perform()
{
    GD_ModularObject* owner = getOwner();

    if(!owner->collisions.floor && !owner->collisions.jumping && !owner->collisions.tileAboveLadder && !owner->collisions.climbing)
    {
        //cout << "floor";
        owner->move(0, GRAVITY);
    }

    if(owner->collisions.groundClip)
    {
        //cout << "clip";
        owner->move(0, GROUNDCLIPAMOUNT+1);

        //prevents clipping into walls, doesnt really work
        if(owner->collisions.wallRight)
            //owner->getSprite()->setPosition({savedX+5+0.f, owner->getSprite()->getPosition().y});
            owner->move(-PLAYERMOVEMENTSPEED+5, 0);
        if(owner->collisions.wallLeft)
            //owner->getSprite()->setPosition({savedX-5+0.f, owner->getSprite()->getPosition().y});
            owner->move(PLAYERMOVEMENTSPEED-5, 0);
    }

    if(owner->collisions.wallRight)
        if(owner->getSprite()->getPosition().x > savedX)
        {
            //cout << "wallright";
            owner->getSprite()->setPosition({savedX+0.f, owner->getSprite()->getPosition().y});
        }

    if(owner->collisions.wallLeft)
        if(owner->getSprite()->getPosition().x < savedX)
        {
            //cout << "wallleft";
            owner->getSprite()->setPosition({savedX+0.f, owner->getSprite()->getPosition().y});
        }

    //saves the last y val when touching the floor, used for jump
    if(!owner->collisions.jumping && owner->collisions.floor && !owner->collisions.climbing)
        ogJumpY = owner->getSprite()->getPosition().y;
    if(owner->collisions.jumping && !owner->collisions.climbing)
    {
        if(owner->collisions.floor || owner->collisions.ceiling)
            owner->collisions.jumping = false;

        if(owner->getSprite()->getPosition().y <= ogJumpY - PLAYERJUMPHEIGHT && !floating && owner->getID() != SPRING)
        {
            floatTimer = 10;
            floating = true;
        }
        else if(owner->getSprite()->getPosition().y <= ogJumpY - SPRINGJUMPHEIGHT && !floating && owner->getID() == SPRING)
        {
            floatTimer = 10;
            floating = true;
        }

        floatTimer--;
        if(!floating)
            owner->move(0, -GRAVITY);
        else if(floatTimer <= 0)
        {
            owner->collisions.jumping = false;
            floating = false;
        }
    }


    //this has to be last
    savedX = owner->getSprite()->getPosition().x;
    savedY = owner->getSprite()->getPosition().y;
}