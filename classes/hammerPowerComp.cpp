#include "hammerPowerComp.hpp"

//handles collecting a hammer power up item
//needs the hammer item to be in a pool
void HammerPowerComp::perform()
{
    GD_ModularObject* player = getOwner();

    if(player->collisions.hammerDuration > 0)
    {
        player->collisions.smash = true;
        if(firstToggle)
        {
            firstToggle = false;
            hammerPool->releaseIntoPool(player->collisions.collidingHammerItem);
            for(int i = 0; i < gameObjectsVector->size(); i++)
                if(gameObjectsVector->at(i) == player->collisions.collidingHammerItem)
                {
                    gameObjectsVector->erase(gameObjectsVector->begin() + i);
                    break;
                }
            player->collisions.collidingHammerItem = nullptr;
        }

        if(player->collisions.collidingHammerItem != nullptr)
            firstToggle = true;

        if(allowbgm && bgmToggle)
        {
            soundManager->stopBGM(BGM);
            soundManager->playBGM(HAMMERBGM);
            bgmToggle = false;
        }
    }
    else if(player->collisions.hammerDuration <= 0)
    {
        player->collisions.smash = false;
        firstToggle = true;
        if(!bgmToggle && allowbgm)
        {
            soundManager->stopBGM(HAMMERBGM);
            soundManager->playBGM(BGM);
            bgmToggle = true;
        }
    }
}