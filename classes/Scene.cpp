#include "Scene.hpp"

Scene::Scene()
{

}

void Scene::load()
{
    score = 0;
    time = 0;
}

void Scene::unLoad()
{
    allObjects.player->collisions.collidingLadder = nullptr;
    allObjects.player->collisions.collidingPlatform = nullptr;
    delete allObjects.player;
    allObjects.player = nullptr;
    delete allObjects.peach;
    allObjects.peach = nullptr;
    delete allObjects.hammer;
    allObjects.hammer = nullptr;

    for(int i = 0; i < allObjects.enemies.size(); i++)
        delete allObjects.enemies.at(i);

    for(int i = 0; i < allObjects.Platforms.size(); i++)
        delete allObjects.Platforms.at(i);

    for(int i = 0; i < allObjects.gameObjects.size(); i++)
        delete allObjects.gameObjects.at(i);

    for(int i = 0; i < allObjects.ladders.size(); i++)
        delete allObjects.ladders.at(i);

    allObjects.platformEnds.clear();
    allObjects.aboveLadder.clear();
    allObjects.enemies.clear();
    allObjects.Platforms.clear();
    allObjects.gameObjects.clear();
    allObjects.ladders.clear();
}

int Scene::update()
{
    float deltaTime = clock.restart().asSeconds();
    time += deltaTime;

    updateAllCollisions(allObjects);

    if(allObjects.player->getHP() <= 0)
        return LOST;
    else if(winCondition)
        return WIN;
    else 
        return ONGOING;
}

//draw order matters for layering
void Scene::draw(RenderWindow* window)
{
    for(int i = 0; i < allObjects.Platforms.size(); i++)
        if(allObjects.Platforms.at(i)->isVisible() == true)
            allObjects.Platforms.at(i)->draw(window);

    for(int i = 0; i < allObjects.aboveLadder.size(); i++)
        if(allObjects.aboveLadder.at(i)->isVisible() == true)
            allObjects.aboveLadder.at(i)->draw(window);

    for(int i = 0; i < allObjects.ladders.size(); i++)
        if(allObjects.ladders.at(i)->isVisible() == true)
            allObjects.ladders.at(i)->draw(window);
            
    for(int i = 0; i < allObjects.gameObjects.size(); i++)
        if(allObjects.gameObjects.at(i)->isVisible() == true)
            allObjects.gameObjects.at(i)->draw(window);

    for(int i = 0; i < allObjects.enemies.size(); i++)
        if(allObjects.enemies.at(i)->isVisible() == true)
            allObjects.enemies.at(i)->draw(window);

    for(int i = 0; i < allObjects.platformEnds.size(); i++)
        if(allObjects.platformEnds.at(i)->isVisible() == true)
            allObjects.platformEnds.at(i)->draw(window);

    if(allObjects.player->isVisible() == true)
        allObjects.player->draw(window);
    if(allObjects.peach && allObjects.peach->isVisible() == true)
        allObjects.peach->draw(window);
    if(allObjects.hammer->isVisible() == true)
        allObjects.hammer->draw(window);
}

void Scene::updateAllCollisions(AllObjects allObjects)
{
    //player
    allObjects.player->collisions.walkLeft = false;
    allObjects.player->collisions.walkRight = false;
    allObjects.player->collisions.groundClip = false;
    allObjects.player->collisions.floor = false;
    for(int i = 0; i < allObjects.Platforms.size(); i++)
        if(checkFloorCollison(allObjects.player, allObjects.Platforms.at(i)))
        {
            allObjects.player->collisions.floor = true;
            if(allObjects.player->collisions.floor)
                allObjects.player->collisions.collidingPlatform = allObjects.Platforms.at(i);
            else
                allObjects.player->collisions.collidingPlatform = nullptr;
            break;
        }

    allObjects.player->collisions.wallRight = false;
    for(int i = 0; i < allObjects.Platforms.size(); i++)
        if(checkWallRightCollison(allObjects.player, allObjects.Platforms.at(i)))
        {
            allObjects.player->collisions.wallRight = true;

            if(checkGroundClipCollison(allObjects.player, allObjects.Platforms.at(i)))
            {
                allObjects.player->collisions.groundClip = true;
                break;
            }
            break;
        }
        else if(allObjects.player->getSprite()->getPosition().x + allObjects.player->getWidth() >= TILESCALE * 28)
        {
            allObjects.player->collisions.wallRight = true;
            break;
        }

    allObjects.player->collisions.wallLeft = false;
    for(int i = 0; i < allObjects.Platforms.size(); i++)
        if(checkWallLeftCollison(allObjects.player, allObjects.Platforms.at(i)))
        {
            allObjects.player->collisions.wallLeft = true;

            if(checkGroundClipCollison(allObjects.player, allObjects.Platforms.at(i)))
            {
                allObjects.player->collisions.groundClip = true;
                break;
            }
            break;
        }
        else if(allObjects.player->getSprite()->getPosition().x <= 0)
        {
            allObjects.player->collisions.wallLeft= true;
            break;
        }
            
    allObjects.player->collisions.ceiling = false;
    for(int i = 0; i < allObjects.Platforms.size(); i++)
        if(checkCeilingCollison(allObjects.player, allObjects.Platforms.at(i)))
        {
            allObjects.player->collisions.ceiling = true;
            break;
        }
            
    allObjects.player->collisions.enemy = false;
    for(int i = 0; i < allObjects.enemies.size(); i++)
        if(allObjects.enemies.at(i)->isVisible() && !allObjects.enemies.at(i)->getDeathStatus() && checkEnemyCollison(allObjects.player, allObjects.enemies.at(i)))
        {
            allObjects.player->collisions.enemy = true; 
            break;
        }
    
    //uses enemy collision func cuz it has the overlap logic
    allObjects.player->collisions.ladder = false;
    for(int i = 0; i < allObjects.ladders.size(); i++)
        if(checkEnemyCollison(allObjects.player, allObjects.ladders.at(i)) && !allObjects.player->collisions.climbing)
        {
            allObjects.player->collisions.ladder = true; 
            allObjects.player->collisions.collidingLadder = allObjects.ladders.at(i);
            break;
        }

    //uses floor collision func cuz it has the overlap  logic
    allObjects.player->collisions.tileAboveLadder = false;
    for(int i = 0; i < allObjects.aboveLadder.size(); i++)
        if(checkFloorCollison(allObjects.player, allObjects.aboveLadder.at(i)))
        {
            allObjects.player->collisions.tileAboveLadder = true;
            allObjects.player->collisions.floor = true;
            
            if(!allObjects.player->collisions.climbing)
                allObjects.player->collisions.collidingLadder = allObjects.aboveLadder.at(i);
            break;
        }

    allObjects.player->collisions.hammerDuration--;
    for(int i = 0; i < allObjects.gameObjects.size(); i++)
        if(allObjects.gameObjects.at(i)->getID() == HAMMERITEM && checkEnemyCollison(allObjects.player, allObjects.gameObjects.at(i)))
        {
            allObjects.player->collisions.hammerDuration = HAMMERPOWERUPDURATION;
            allObjects.player->collisions.collidingHammerItem = allObjects.gameObjects.at(i);
            break;
        }
    
    //peach
    if(allObjects.peach)
    {
        allObjects.peach->collisions.floor = false;
        for(int i = 0; i < allObjects.Platforms.size(); i++)
            if(checkFloorCollison(allObjects.peach, allObjects.Platforms.at(i)))
            {
                allObjects.peach->collisions.floor = true;
                if(allObjects.peach->collisions.floor)
                    allObjects.peach->collisions.collidingPlatform = allObjects.Platforms.at(i);
                else
                    allObjects.peach->collisions.collidingPlatform = nullptr;
                break;
            }
    }
    //enemies
    for(int k = 0; k < allObjects.enemies.size(); k++)
    {
        allObjects.enemies.at(k)->collisions.groundClip = false;
        allObjects.enemies.at(k)->collisions.floor = false;
        for(int i = 0; i < allObjects.Platforms.size(); i++)
            if(checkFloorCollison(allObjects.enemies.at(k), allObjects.Platforms.at(i)))
            {
                allObjects.enemies.at(k)->collisions.floor = true; 
                break;
            }
                
        allObjects.enemies.at(k)->collisions.wallRight = false;
        for(int i = 0; i < allObjects.Platforms.size(); i++)
            if(checkWallRightCollison(allObjects.enemies.at(k), allObjects.Platforms.at(i)))
            {
                allObjects.enemies.at(k)->collisions.wallRight = true;

                if(checkGroundClipCollison(allObjects.enemies.at(k), allObjects.Platforms.at(i)))
                {
                    allObjects.enemies.at(k)->collisions.groundClip = true;
                    break;
                }
                break;
            }

        allObjects.enemies.at(k)->collisions.wallLeft = false;
        for(int i = 0; i < allObjects.Platforms.size(); i++)
            if(checkWallLeftCollison(allObjects.enemies.at(k), allObjects.Platforms.at(i)))
            {
                allObjects.enemies.at(k)->collisions.wallLeft = true;

                if(checkGroundClipCollison(allObjects.enemies.at(k), allObjects.Platforms.at(i)))
                {
                    allObjects.enemies.at(k)->collisions.groundClip = true;
                    break;
                }
                break;
            }
                
        allObjects.enemies.at(k)->collisions.ceiling = false;
        for(int i = 0; i < allObjects.Platforms.size(); i++)
            if(checkCeilingCollison(allObjects.enemies.at(k), allObjects.Platforms.at(i)))
            {
                allObjects.enemies.at(k)->collisions.ceiling = true;
                break;
            }
                
        allObjects.enemies.at(k)->collisions.player = false;
        if(checkEnemyCollison(allObjects.enemies.at(k), allObjects.player))
            allObjects.enemies.at(k)->collisions.player = true;   
            
        allObjects.enemies.at(k)->collisions.tileAboveLadder = false;
        for(int i = 0; i < allObjects.aboveLadder.size(); i++)
            if(checkFloorCollison(allObjects.enemies.at(k), allObjects.aboveLadder.at(i)))
            {
                allObjects.enemies.at(k)->collisions.tileAboveLadder = true;
                allObjects.enemies.at(k)->collisions.floor = true;
                break;
            }

        allObjects.enemies.at(k)->collisions.platformEnd = false;
        for(int i = 0; i < allObjects.platformEnds.size(); i++)
            if(checkPlatformEndCollision(allObjects.enemies.at(k), allObjects.platformEnds.at(i)))
            {
                allObjects.enemies.at(k)->collisions.platformEnd = true;
                break;
            }
        
    }
}

bool Scene::checkFloorCollison(GD_ModularObject* main, GD_ModularObject* target)
{
    return main->getSprite()->getPosition().x < target->getSprite()->getPosition().x + target->getWidth() &&
            target->getSprite()->getPosition().x < main->getSprite()->getPosition().x + main->getWidth() &&
           main->getSprite()->getPosition().y + main->getHeight() >= target->getSprite()->getPosition().y &&
           main->getSprite()->getPosition().y + main->getHeight() - target->getSprite()->getPosition().y <= COLLISIONLEEWAY;
}

bool Scene::checkWallRightCollison(GD_ModularObject* main, GD_ModularObject* target)
{
    return (main->getSprite()->getPosition().x + main->getWidth() >= target->getSprite()->getPosition().x) &&  
            (main->getSprite()->getPosition().x < target->getSprite()->getPosition().x) &&
            (main->getSprite()->getPosition().y + main->getHeight() > target->getSprite()->getPosition().y) && 
            (main->getSprite()->getPosition().y < target->getSprite()->getPosition().y + target->getHeight());
}

bool Scene::checkWallLeftCollison(GD_ModularObject* main, GD_ModularObject* target)
{
    return (main->getSprite()->getPosition().x <= target->getSprite()->getPosition().x + target->getWidth()) &&
           (main->getSprite()->getPosition().x + main->getWidth() > target->getSprite()->getPosition().x + target->getWidth()) && 
           (main->getSprite()->getPosition().y + main->getHeight() > target->getSprite()->getPosition().y) && 
           (main->getSprite()->getPosition().y < target->getSprite()->getPosition().y + target->getHeight());
}

bool Scene::checkCeilingCollison(GD_ModularObject* main, GD_ModularObject* target)
{
    return main->getSprite()->getPosition().x < target->getSprite()->getPosition().x + target->getWidth() &&
            target->getSprite()->getPosition().x < main->getSprite()->getPosition().x + main->getWidth() &&
            main->getSprite()->getPosition().y <= target->getSprite()->getPosition().y + target->getHeight() &&
            (target->getSprite()->getPosition().y + target->getHeight() - main->getSprite()->getPosition().y) <= COLLISIONLEEWAY;
}

bool Scene::checkEnemyCollison(GD_ModularObject* main, GD_ModularObject* target)
{
    return main->getSprite()->getPosition().x < target->getSprite()->getPosition().x + target->getWidth() &&
            target->getSprite()->getPosition().x < main->getSprite()->getPosition().x + main->getWidth() &&
            main->getSprite()->getPosition().y < target->getSprite()->getPosition().y + target->getHeight() &&
            target->getSprite()->getPosition().y < main->getSprite()->getPosition().y + main->getHeight();
}

bool Scene::checkGroundClipCollison(GD_ModularObject* main, GD_ModularObject* target)
{
    return main->getSprite()->getPosition().y + main->getHeight() - GROUNDCLIPAMOUNT <= target->getSprite()->getPosition().y;
}

bool Scene::checkLadderCollison(GD_ModularObject* main, GD_ModularObject* target)
{
    return main->getSprite()->getPosition().x < target->getSprite()->getPosition().x + target->getWidth()+1 &&
            target->getSprite()->getPosition().x < main->getSprite()->getPosition().x + main->getWidth() &&
            main->getSprite()->getPosition().y + main->getHeight() > target->getSprite()->getPosition().y;
}
bool Scene::checkAboveLadderCollision(GD_ModularObject* main, GD_ModularObject* target){
    return main->getSprite()->getPosition().x < target->getSprite()->getPosition().x + target->getWidth() &&
            target->getSprite()->getPosition().x < main->getSprite()->getPosition().x + main->getWidth() &&
            main->getSprite()->getPosition().y + main->getHeight() > target->getSprite()->getPosition().y;
}
bool Scene::checkPlatformEndCollision(GD_ModularObject* main, GD_ModularObject* target){
    return main->getSprite()->getPosition().x == target->getSprite()->getPosition().x &&
            main->getSprite()->getPosition().y + main->getHeight() == target->getSprite()->getPosition().y;
}