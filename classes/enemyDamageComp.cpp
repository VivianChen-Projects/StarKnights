#include "enemyDamageComp.hpp"

//makes player take damage when hitting an enemy
//the invul thing ended up not getting used since we kept mario at 1 hp
void EnemyDamageComp::perform()
{
    GD_ModularObject* owner = getOwner();

    invulTimer--;
    if(owner->collisions.enemy && invulTimer <= 0)
    {
        owner->setHP(owner->getHP() - 1);
        invulTimer = PLAYERINVULTIME;
    }
}