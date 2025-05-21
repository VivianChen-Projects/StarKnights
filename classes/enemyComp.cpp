#include "enemyComp.h"

void EnemyComp::perform(){
    if(!getEnabled())
        return;

    GD_ModularObject* owner = getOwner();

    if(owner->getID() == FIREBALL){
        if(owner->getMovingDirection()==LEFT)
            GD_Trn::moveLeft(owner);
        else if(owner->getMovingDirection()==RIGHT)
            GD_Trn::moveRight(owner);
        
        if(owner->collisions.platformEnd){
            if(owner->getMovingDirection()==LEFT){
                owner->setMovingDirection(RIGHT);
                owner->move(FIREBALLMOVEMENTSPEED,0);
            }
            else if(owner->getMovingDirection()==RIGHT){
                owner->setMovingDirection(LEFT);
                owner->move(-FIREBALLMOVEMENTSPEED,0);
            }
        }
    }

    if(owner->getID() == BARREL){
        if(owner->collisions.floor){
            if(owner->getMovingDirection()==LEFT){
                while(time <= FRAMERATE/10){
                    time ++;
                    GD_Trn::moveLeft(owner);
                }
            }
            else if(owner->getMovingDirection()==RIGHT){
                while(time <= FRAMERATE/10){
                    time++;
                    GD_Trn::moveRight(owner);
                }
            }
            time = 0;
        }
    }

    if(owner->getID() == SPRING){
        if(owner->getMovingDirection()==LEFT){
            owner->move(-SPRINGMOVEMENTSPEED,0);
            if(owner->collisions.floor && !owner->collisions.jumping){
                owner->collisions.jumping = true;
                owner->collisions.floor = false;
            }
        }
        else if(owner->getMovingDirection()==RIGHT){
            owner->move(SPRINGMOVEMENTSPEED,0);
            if(owner->collisions.floor && !owner->collisions.jumping){
                owner->collisions.jumping = true;
                owner->collisions.floor = false;
            }
           
        }
    }
}