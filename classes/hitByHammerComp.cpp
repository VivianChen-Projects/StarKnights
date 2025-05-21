#include "hitByHammerComp.hpp"

//only for enemies, kills them when touching mario's hammer
void HitByHammerComp::perform()
{
    GD_ModularObject* owner = getOwner();

    //checks if enemy is overlapping with the hammer
    if(owner->getSprite()->getPosition().x < hammer->getSprite()->getPosition().x + hammer->getWidth() &&
    hammer->getSprite()->getPosition().x < owner->getSprite()->getPosition().x + owner->getWidth() &&
    owner->getSprite()->getPosition().y < hammer->getSprite()->getPosition().y + hammer->getHeight() &&
    hammer->getSprite()->getPosition().y < owner->getSprite()->getPosition().y + owner->getHeight() &&
    owner->getHP() > 0 && hammer->isVisible())
    {
        owner->setHP(0);
        owner->setDead(true);
        soundManager->playSFX(ENEMYDEATH, false);
    }
}