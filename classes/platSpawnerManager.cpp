#include "platSpawnerManager.hpp"

void PlatSpawnerManager::giveScenePlatformsVector(vector<GD_ModularObject*>* Platforms)
{
    scenePlatforms = Platforms;
}

void PlatSpawnerManager::giveScenePlayer(GD_ModularObject* player)
{
    Player = player;
}

void PlatSpawnerManager::makeNewSpawner(float Speed, int TilesInBewteenPlats, int DistanceInTiles, Direction Direction, int startXinTiles, int startYinTiles)
{
    Spawner newSpawner;
    newSpawner.speed = Speed;
    newSpawner.direction = Direction;
    newSpawner.distance = DistanceInTiles * TILESCALE;
    newSpawner.startX = startXinTiles * TILESCALE;
    newSpawner.startY = startYinTiles * TILESCALE;

    int size = ((DistanceInTiles * TILESCALE) / (TilesInBewteenPlats * TILESCALE)) * 2;

    for(int i = 0; i < size; i++)
    {
        GD_ModularObject* newPlat;

        //left platform
        if(i == 0) //index 0 is separete cuz you cant divide a 0 smh
            newPlat = objectFactory.makePlatform(startXinTiles, startYinTiles);
        else if(i % 2 == 0)
            newPlat = objectFactory.makePlatform(startXinTiles, startYinTiles + TilesInBewteenPlats * (i / 2));
        //right platform
        else
            newPlat = objectFactory.makePlatform(startXinTiles + 1, startYinTiles + TilesInBewteenPlats * (i / 2));

        if(Direction == Direction::up)
            newPlat->attachComponent(new ConstantMoveComp(newPlat, "up", ConstantMoveComp::Direction::up, Speed));
        else if(Direction == Direction::down)
            newPlat->attachComponent(new ConstantMoveComp(newPlat, "down", ConstantMoveComp::Direction::down, Speed));

        newSpawner.Plats.push_back(newPlat);
        scenePlatforms->push_back(newPlat);
    }

    spawners.push_back(newSpawner);
}

void PlatSpawnerManager::update()
{
    //TPs the platforms when distance is reached
    for(int i = 0; i < spawners.size(); i++)
        for(int k = 0; k < spawners.at(i).Plats.size(); k++)
            if(spawners.at(i).direction == Direction::up && spawners.at(i).Plats.at(k)->getSprite()->getPosition().y <= spawners.at(i).startY - spawners.at(i).distance)
                spawners.at(i).Plats.at(k)->move(0, -spawners.at(i).distance);
            else if(spawners.at(i).direction == Direction::down && spawners.at(i).Plats.at(k)->getSprite()->getPosition().y >= spawners.at(i).startY)
                spawners.at(i).Plats.at(k)->move(0, spawners.at(i).distance);

    //moves player accordingly when touching plat
    for(int i = 0; i < spawners.size(); i++)
        for(int k = 0; k < spawners.at(i).Plats.size(); k++)
            if(spawners.at(i).Plats.at(k) == Player->collisions.collidingPlatform && Player->collisions.floor)
                if(spawners.at(i).direction == Direction::up)
                    Player->move(0, spawners.at(i).speed);
                else if(spawners.at(i).direction == Direction::down)    
                    Player->move(0, -spawners.at(i).speed);
}

void PlatSpawnerManager::reset()
{
    for(int i = 0; i < spawners.size(); i++)
        spawners.at(i).Plats.clear();
    spawners.clear();
}

PlatSpawnerManager::~PlatSpawnerManager()
{
    for(int i = 0; i < spawners.size(); i++)
        spawners.at(i).Plats.clear();
    spawners.clear();
    
    scenePlatforms = nullptr;
    Player = nullptr;
}