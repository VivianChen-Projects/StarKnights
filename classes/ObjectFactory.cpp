#include "ObjectFactory.h"

//makes all the objs and inits them 

GD_ModularObject*  ObjectFactory::makePlayer(int x,int y){
    GD_ModularObject* player = new GD_ModularObject(PLAYER, "assets/og_Mario_Sheet.png", 0, 0);
    player->setFrameXY(7,5);
    player->setSprite();
    player->scaleObject(0.5);
    player->setTileXY(x, y);
    player->attachComponent(new PlayerMoveComp(player));
    player->attachComponent(new PhysicsComp(player));
    player->attachComponent(new LadderComp(player));
    player->attachComponent(new SpriteComp(player));
    player->attachComponent(new EnemyDamageComp(player));
    return player;
}

GD_ModularObject*  ObjectFactory::makeEnemy(string state, int x,int y){
    GD_ModularObject* enemy = new GD_ModularObject(ENEMY, "assets/og_DK_Sheet.png", 0, 0);
    enemy->setFrameXY(4,4);
    enemy->setSprite();
    enemy->setTileXY(x, y);
    enemy->setState(state);
    enemy->attachComponent(new EnemyComp(enemy));
    enemy->attachComponent(new PhysicsComp(enemy));
    enemy->attachComponent(new SpriteComp(enemy));
    return enemy;
};

GD_ModularObject*  ObjectFactory::makePeach(int x,int y){
    GD_ModularObject* peach = new GD_ModularObject(PEACH, "assets/og_Peach_Sheet.png", 0, 0);
    peach->setFrameXY(3,2);
    peach->setSprite();
    peach->scaleObject(0.5);
    peach->setTileXY(x, y);
    return peach;
};

GD_ModularObject*  ObjectFactory::makePlatform(int x,int y){
    GD_ModularObject* platform = new GD_ModularObject(PLATFORM, "assets/og_RedGirder.png");
    platform->setTileXY(x, y);
    return platform;
};

GD_ModularObject*  ObjectFactory::makeLadder(int x,int y){
    GD_ModularObject* ladder = new GD_ModularObject(LADDER, "assets/og_Ladder.png");
    ladder->setTileXY(x, y);
    return ladder;
};

GD_ModularObject*  ObjectFactory::makeSpawner(string direction, int x,int y){
    GD_ModularObject* spawner = new GD_ModularObject(SPAWNER, "assets/og_PlatformSpawner.png");
    
    if(direction == UP){
        spawner->setTileXY(x, y);
    }
    if(direction == DOWN){
        spawner->getSprite()->rotate(sf::degrees(180));
        spawner->setTileXY(x+1, y-1);
    }
    if(direction == LEFT){
        spawner->getSprite()->rotate(sf::degrees(-90));
        spawner->setTileXY(x-1, y);
    }
    if(direction == RIGHT){
        spawner->getSprite()->rotate(sf::degrees(90));
        spawner->setTileXY(x+1, y);
    }
    return spawner;
};

GD_ModularObject*  ObjectFactory::makeSpawnerRope(int x,int y){
    GD_ModularObject* rope = new GD_ModularObject(ROPE, "assets/og_PlatformSpawnerRope.png");
    rope->setTileXY(x, y);
    return rope;
};

GD_ModularObject*  ObjectFactory::makeFireBall(string moveDirection, int x,int y){
    GD_ModularObject* fireBall = new GD_ModularObject(FIREBALL, "assets/og_Fireball_Sheet.png",0,0);
    fireBall->setFrameXY(4,3);
    fireBall->setSprite();
    fireBall->scaleObject(0.5);
    fireBall->setTileXY(x, y);
    fireBall->attachComponent(new EnemyComp(fireBall));
    fireBall->attachComponent(new PhysicsComp(fireBall));
    fireBall->attachComponent(new SpriteComp(fireBall));
    fireBall->setMovingDirection(moveDirection);
    return fireBall;
};

GD_ModularObject*  ObjectFactory::makeSpring(string moveDirection, int x,int y){
    GD_ModularObject* spring = new GD_ModularObject(SPRING, "assets/og_Spring_Sheet.png",0,0);
    spring->setFrameXY(4,2);
    spring->setSprite();
    spring->scaleObject(0.5);
    spring->setTileXY(x, y);
    spring->attachComponent(new PhysicsComp(spring));
    spring->attachComponent(new EnemyComp(spring));
    spring->attachComponent(new SpriteComp(spring));
    spring->setMovingDirection(moveDirection);
    spring->collisions.climbing = false;
    return spring;
};

GD_ModularObject*  ObjectFactory::makeBarrel(string moveDirection, int x,int y){
    GD_ModularObject* barrel = new GD_ModularObject(BARREL, "assets/og_Barrel_Sheet.png", 0, 0);
    barrel->setFrameXY(4,4);
    barrel->setSprite();
    barrel->setTileXY(x, y);
    barrel->attachComponent(new EnemyComp(barrel));
    barrel->attachComponent(new PhysicsComp(barrel));
    barrel->attachComponent(new SpriteComp(barrel));
    barrel->setMovingDirection(moveDirection);
    return barrel;
};

GD_ModularObject*  ObjectFactory::makeHammer(GD_ModularObject* player){
    GD_ModularObject* hammer = new GD_ModularObject(HAMMER, "assets/og_Hammer_Sheet.png", 0, 0);
    hammer->setFrameXY(2,4);
    hammer->setSprite();
    hammer->getSprite()->setPosition({player->getSprite()->getPosition().x, (player->getSprite()->getPosition().y/24) - 2 * TILESCALE});
    hammer->attachComponent(new HammerComp(hammer));
    hammer->scaleObject(0.5);
    hammer->toggleVisibility();
    player->attachChild(hammer);
    return hammer;
};



