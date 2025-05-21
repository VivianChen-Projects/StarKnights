#include "movingPlatComp.hpp"

//moves 1 platform block back and forth
void MovingPlatComp::perform()
{
    if(!getEnabled())
        return;

    GD_ModularObject* owner = getOwner();
    cooldown--;

    //going horizontally
    if(startDirection == Direction::left || startDirection == Direction::right)
    {
        if(start)
        {
            start = false;
            owner->attachComponent(new ConstantMoveComp(owner, "left", ConstantMoveComp::Direction::left, speed));
            owner->attachComponent(new ConstantMoveComp(owner, "right", ConstantMoveComp::Direction::right, speed));
            leftComp = owner->getComponent("left");
            if(leftComp)
                leftComp->setEnabled(false);
            rightComp = owner->getComponent("right");
            if(rightComp)
                rightComp->setEnabled(false);

            startingCoord = owner->getSprite()->getPosition().x;

            //going left first
            if(startDirection == Direction::left && leftComp)
                leftComp->setEnabled(true);
            //going right first
            else if(startDirection == Direction::right && rightComp)
                rightComp->setEnabled(true);
        }

        //reverses direction 
        if(owner->getSprite()->getPosition().x >= startingCoord + (distance * TILESCALE) || owner->getSprite()->getPosition().x <= startingCoord - (distance * TILESCALE) || (owner->getSprite()->getPosition().x >= startingCoord - 1 && owner->getSprite()->getPosition().x <= startingCoord + 1))
            if(cooldown <= 0)
                reverseDirection();
    }

    //going vertically
    if(startDirection == Direction::up || startDirection == Direction::down)
    {
        if(start)
        {
            start = false;
            owner->attachComponent(new ConstantMoveComp(owner, "up", ConstantMoveComp::Direction::up, speed));
            owner->attachComponent(new ConstantMoveComp(owner, "down", ConstantMoveComp::Direction::down, speed));
            upComp = owner->getComponent("up");
            if(upComp)
                upComp->setEnabled(false);
            downComp = owner->getComponent("down");
            if(downComp)
                downComp->setEnabled(false);

            startingCoord = owner->getSprite()->getPosition().y;

            //going up first
            if(startDirection == Direction::up && upComp)
                upComp->setEnabled(true);
            //going down first
            else if(startDirection == Direction::down && downComp)
                downComp->setEnabled(true);
        }

        //reverses direction 
        if(owner->getSprite()->getPosition().y >= startingCoord + (distance * TILESCALE) || owner->getSprite()->getPosition().y <= startingCoord - (distance * TILESCALE) || (owner->getSprite()->getPosition().y >= startingCoord - 1 && owner->getSprite()->getPosition().y <= startingCoord + 1))
            if(cooldown <= 0)
                reverseDirection();
    }

    //moves player when touching this
    if(player->collisions.collidingPlatform && owner == player->collisions.collidingPlatform && player->collisions.floor)
        if(leftComp && leftComp->getEnabled())
            player->move(-speed, 0);
        else if(rightComp && rightComp->getEnabled())
            player->move(speed, 0);
        else if(upComp && upComp->getEnabled())
            player->move(0, speed);
        else if(downComp && downComp->getEnabled())
            player->move(0, -speed);
}

void MovingPlatComp::reverseDirection()
{
    if(startDirection == Direction::left || startDirection == Direction::right)
        if(leftComp->getEnabled() && leftComp && rightComp)
        {
            leftComp->setEnabled(false);
            rightComp->setEnabled(true);
            cooldown = 60;
        }
        else
        {
            leftComp->setEnabled(true);
            rightComp->setEnabled(false);
            cooldown = 60;
        }

    if(startDirection == Direction::up || startDirection == Direction::down)
        if(upComp->getEnabled() && upComp && downComp)
        {
            upComp->setEnabled(false);
            downComp->setEnabled(true);
            cooldown = 60;
        }
        else
        {
            upComp->setEnabled(true);
            downComp->setEnabled(false);
            cooldown = 60;
        }
}