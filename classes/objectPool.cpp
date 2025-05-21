#include "objectPool.hpp"

//pool doesnt initialize/change anything about the objects

objectPool::objectPool(string objName, string textureName, int poolSize, bool isAnimated)
{
    if(!isAnimated)
        for(int i = 0; i < poolSize; i++)
        {
            GD_ModularObject* newObject = new GD_ModularObject(objName, textureName);
            pool.push_back(newObject);
        }
    else
        for(int i = 0; i < poolSize; i++)
        {
            GD_ModularObject* newObject = new GD_ModularObject(objName, textureName, 0, 0);
            pool.push_back(newObject);
        }
}

GD_ModularObject* objectPool::requestFromPool()
{
    for(int i = 0; i < pool.size(); i++)
        if(pool.at(i) != nullptr)
        {
            GD_ModularObject* temp = pool.at(i);
            temp->enableAllComps();
            temp->setReturnToPool(false);
            temp->setHP(1);
            if(temp->getID() == FIREBALL)
            {
                temp->getSprite()->setTextureRect(IntRect({0,0},{16,16}));
            }
            temp->setDead(false);
            if(!temp->isVisible())
                temp->toggleVisibility();
            pool.at(i) = nullptr;
            return temp;
        }

    //else if pool is empty
    return nullptr;
}

void objectPool::releaseIntoPool(GD_ModularObject* object)
{
    object->disableAllComps();
    if(object->isVisible())
        object->toggleVisibility();
    
    for(int i = 0; i < pool.size(); i++)
        if(pool.at(i) == nullptr)
        {
            pool.at(i) = object;
            return;
        }
}

void objectPool::givePoolConstantMoveComp(string direction, float speed)
{
    if(pool.size() <= 0)
        return;

    if(direction == UP)
        for(int i = 0; i < pool.size(); i++)
        {
            pool.at(i)->attachComponent(new ConstantMoveComp(pool.at(i), "up", ConstantMoveComp::Direction::up, speed));
            pool.at(i)->disableComponent("up");
        }

    if(direction == DOWN)
        for(int i = 0; i < pool.size(); i++)
        {
            pool.at(i)->attachComponent(new ConstantMoveComp(pool.at(i), "down", ConstantMoveComp::Direction::down, speed));
            pool.at(i)->disableComponent("down");
        }
}

int objectPool::getAvailableSize()
{
    int counter = 0;

    for(int i = 0; i < pool.size(); i++)
        if(pool.at(i) != nullptr)
            counter++;

    return counter;
}

void objectPool::setUpFireballPool(GD_ModularObject* player, GD_ModularObject* hammer, SoundManager* soundManager)
{
    for(int i = 0; i < pool.size(); i++)
    {
        pool.at(i)->setFrameXY(4,3);
        pool.at(i)->setSprite();
        pool.at(i)->scaleObject(0.5);
        pool.at(i)->setTileXY(0, 0);
        pool.at(i)->attachComponent(new EnemyComp(pool.at(i)));
        pool.at(i)->attachComponent(new PhysicsComp(pool.at(i)));
        pool.at(i)->attachComponent(new SpriteComp(pool.at(i)));
        pool.at(i)->attachComponent(new HitByHammerComp(pool.at(i), player, hammer, soundManager));
        pool.at(i)->setMovingDirection(RIGHT);
    }
}
