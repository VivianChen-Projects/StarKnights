#include "HSR.h"

void HSR::load()
{
    //intro stuff
    introToggle = true;
    introDuration = 100;

    Text title(bold, "Why Does Life Slumber...", 50);
    title.setPosition({TILESCALE*3, TILESCALE*12});
    title.setFillColor(Color::White);
    texts.push_back(title);

    Text inspo(light, "Music and Title from Honkai: Star Rail", 20);
    inspo.setPosition({TILESCALE*8, TILESCALE*11});
    inspo.setFillColor(Color::White);
    texts.push_back(inspo);

    Text load(light, "Loading...", 20);
    load.setPosition({TILESCALE*25-10, TILESCALE*30});
    load.setFillColor(Color::White);
    texts.push_back(load);


    //stage sound
    soundManager.addBGM("assets/WHITE NIGHT.mp3", BGM);
    soundManager.playBGM(BGM);
    soundManager.addSFX("assets/jump.wav", JUMPSFX);
    soundManager.addSFX("assets/walking.wav", WALKINGSFX);

    //stage
    allObjects.player = objectFactory.makePlayer(26,30);
    allObjects.player->move(1,0);
    allObjects.player->attachComponent(new SfxComp(allObjects.player, &soundManager));
    allObjects.hammer = objectFactory.makeHammer(allObjects.player);
    allObjects.player->disableComponent("PlayerMoveComp");
    allObjects.peach = objectFactory.makePeach(18,1);
    allObjects.peach->getSprite()->rotate(sf::degrees(90));
    float w = allObjects.peach->getFrameW()/allObjects.peach->getFrameX();
    float h = allObjects.peach->getFrameH()/allObjects.peach->getFrameY();
    allObjects.peach->getSprite()->setOrigin({w/2,h/2});

    Text ob(light, "OBJECTIVE:", 20);
    ob.setPosition({TILESCALE*21, TILESCALE*2});
    ob.setFillColor(Color::White);
    objective.push_back(ob);

    Text reach(light, "Reach the sleeping princess", 20);
    reach.setPosition({TILESCALE*17, TILESCALE*3});
    reach.setFillColor(Color::White);
    objective.push_back(reach);

    // first floor
    allObjects.enemies.push_back(objectFactory.makeBarrel(RIGHT,0,8));
    allObjects.enemies.push_back(objectFactory.makeSpring(RIGHT,3,8));
    allObjects.Platforms.push_back(objectFactory.makePlatform(27, 31));
    allObjects.Platforms.push_back(objectFactory.makePlatform(26, 31));
    allObjects.Platforms.push_back(objectFactory.makePlatform(25, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(21, 30));
    
    allObjects.platformEnds.push_back(objectFactory.makePlatform(16, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(16, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(15, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(14, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(13, 30));
    allObjects.platformEnds.push_back(objectFactory.makePlatform(12, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(12, 30));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(16, 31));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(12, 31));
    
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(9, 31));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(9, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(9, 29));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(5, 31));
    allObjects.Platforms.push_back(objectFactory.makePlatform(5, 30));

    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(2, 31));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(0, 31));
    allObjects.Platforms.push_back(objectFactory.makePlatform(2, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(1, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(0, 30));

    allObjects.ladders.push_back(objectFactory.makeLadder(1, 29));
    allObjects.ladders.push_back(objectFactory.makeLadder(1, 28));
    allObjects.ladders.push_back(objectFactory.makeLadder(1, 27));
    allObjects.ladders.push_back(objectFactory.makeLadder(1, 26));

    allObjects.enemies.push_back(objectFactory.makeFireBall(RIGHT, 13, 29));
    
    //second floor
    allObjects.aboveLadder.push_back(objectFactory.makePlatform(1, 25));

    allObjects.Platforms.push_back(objectFactory.makePlatform(0, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(2, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(3, 25));

    allObjects.Platforms.push_back(objectFactory.makePlatform(6, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(7, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(8, 25));

    allObjects.Platforms.push_back(objectFactory.makePlatform(11, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(14, 24));
    allObjects.Platforms.push_back(objectFactory.makePlatform(17, 25));

    platSpawnerManager.giveScenePlatformsVector(&allObjects.Platforms);
    platSpawnerManager.giveScenePlayer(allObjects.player);
    platSpawnerManager.makeNewSpawner(1, 2, 8, PlatSpawnerManager::Direction::up, 19, 24);
    platSpawnerManager.makeNewSpawner(2, 3, 10, PlatSpawnerManager::Direction::up, 25, 24);
    
    allObjects.Platforms.push_back(objectFactory.makePlatform(25, 13));

    //third floor
    allObjects.platformEnds.push_back(objectFactory.makePlatform(0, 19));
    allObjects.Platforms.push_back(objectFactory.makePlatform(0, 19));
    for(int i = 1; i < 9; i ++){
        allObjects.Platforms.push_back(objectFactory.makePlatform(i, 19));
    }
    allObjects.platformEnds.push_back(objectFactory.makePlatform(9, 19));
    allObjects.Platforms.push_back(objectFactory.makePlatform(9, 19));
    allObjects.enemies.push_back(objectFactory.makeFireBall(RIGHT,2,18));


    allObjects.platformEnds.push_back(objectFactory.makePlatform(6, 15));
    allObjects.Platforms.push_back(objectFactory.makePlatform(6, 15));
    for(int i = 8; i < 21; i ++){
        allObjects.Platforms.push_back(objectFactory.makePlatform(i, 15));
    }
    allObjects.platformEnds.push_back(objectFactory.makePlatform(21, 15));
    allObjects.Platforms.push_back(objectFactory.makePlatform(21, 15));
    allObjects.enemies.push_back(objectFactory.makeFireBall(RIGHT,8,14));
    allObjects.enemies.push_back(objectFactory.makeFireBall(LEFT,19,14));

    allObjects.aboveLadder.push_back(objectFactory.makePlatform(7, 15));
    allObjects.ladders.push_back(objectFactory.makeLadder(7, 16));
    allObjects.ladders.push_back(objectFactory.makeLadder(7, 17));
    allObjects.ladders.push_back(objectFactory.makeLadder(7, 18));

    //fouth floor    
    for(int i = 16; i < 26; i ++){
        allObjects.Platforms.push_back(objectFactory.makePlatform(i, 10));
    }

    allObjects.Platforms.push_back(objectFactory.makePlatform(0,12));
    allObjects.Platforms.back()->move(0, PIXEL * 6);
    allObjects.Platforms.push_back(objectFactory.makePlatform(1,12));
    allObjects.Platforms.back()->move(0, PIXEL * 5);
    allObjects.Platforms.push_back(objectFactory.makePlatform(2,12));
    allObjects.Platforms.back()->move(0, PIXEL * 4);
    allObjects.Platforms.push_back(objectFactory.makePlatform(3,12));
    allObjects.Platforms.back()->move(0, PIXEL * 3);
    allObjects.Platforms.push_back(objectFactory.makePlatform(4,12));
    allObjects.Platforms.back()->move(0, PIXEL * 2);
    allObjects.Platforms.push_back(objectFactory.makePlatform(5,12));
    allObjects.Platforms.back()->move(0, PIXEL);

    allObjects.Platforms.push_back(objectFactory.makePlatform(12, 9));
    allObjects.aboveLadder.push_back(objectFactory.makePlatform(11, 9));
    allObjects.aboveLadder.push_back(objectFactory.makePlatform(13, 9));

    allObjects.ladders.push_back(objectFactory.makeLadder(11, 10));
    allObjects.ladders.push_back(objectFactory.makeLadder(11, 11));
    allObjects.ladders.push_back(objectFactory.makeLadder(11, 12));
    allObjects.ladders.push_back(objectFactory.makeLadder(11, 13));
    allObjects.ladders.push_back(objectFactory.makeLadder(11, 14));

    allObjects.ladders.push_back(objectFactory.makeLadder(23, 7));
    allObjects.ladders.push_back(objectFactory.makeLadder(23, 8));
    allObjects.ladders.push_back(objectFactory.makeLadder(23, 9));

    //fifth floor
    for(int i = 3; i <  25; i ++){
        allObjects.Platforms.push_back(objectFactory.makePlatform(i, 6));
    }
    allObjects.platformEnds.push_back(objectFactory.makePlatform(24, 6));
    allObjects.platformEnds.push_back(objectFactory.makePlatform(18, 6));
    allObjects.aboveLadder.push_back(objectFactory.makePlatform(23, 6));

    allObjects.ladders.push_back(objectFactory.makeLadder(15, 3));
    allObjects.ladders.push_back(objectFactory.makeLadder(15, 4));
    allObjects.ladders.push_back(objectFactory.makeLadder(15, 5));

    allObjects.enemies.push_back(objectFactory.makeEnemy(IDLE, 3, 1));
    allObjects.enemies.push_back(objectFactory.makeFireBall(RIGHT, 20, 5));

    //goal
    for(int i = 16; i < 20; i ++){
        allObjects.Platforms.push_back(objectFactory.makePlatform(i, 2));
    }
    allObjects.aboveLadder.push_back(objectFactory.makePlatform(15, 2));

}

void HSR::unLoad()
{
    Scene::unLoad();
    platSpawnerManager.reset();
    soundManager.reset();
    texts.clear();
    objective.clear();

}

int HSR::update()
{
    intro();

    int returnStatus = Scene::update();
    allObjects.player->update();
    allObjects.hammer->update();
    allObjects.peach->update();

    for(int i = 0; i < allObjects.enemies.size(); i++)
        allObjects.enemies.at(i)->update();

    for(int i = 0; i < allObjects.Platforms.size(); i++)
        allObjects.Platforms.at(i)->update();

    //reset location of spring and barrel
    for(int i = 0; i < allObjects.enemies.size(); i++){
        if(allObjects.enemies.at(i)->getID() == BARREL && allObjects.enemies.at(i)->getSprite()->getPosition().y >= TILESCALE*34)
        {
            barrelSpawnTimer++;
           if(barrelSpawnTimer >= barrelCooldown){
            allObjects.enemies.at(i)->setTileXY(0,8);
            barrelSpawnTimer = 0;
           }
        }
        if(allObjects.enemies.at(i)->getID() == SPRING && allObjects.enemies.at(i)->getSprite()->getPosition().x >= TILESCALE*28)
        {
            springSpawnTimer++;
            if(springSpawnTimer >= springCooldown){
            allObjects.enemies.at(i)->setTileXY(3,8);
            springSpawnTimer = 0;
            }
        }
    }

    platSpawnerManager.update();

    //checks winning condition
    if(checkEnemyCollison(allObjects.player, allObjects.peach)){
        return WIN;
    }

    return returnStatus;
}

void HSR::draw(RenderWindow* window)
{
    if(!introToggle)
    {
        
        for(int i = 0; i < objective.size(); i++)
            window->draw(objective.at(i).value());
        Scene::draw(window);
    }

    if(introToggle)
        for(int i = 0; i < texts.size(); i++)
            window->draw(texts.at(i).value());
}

void HSR::intro()
{
    if(!introToggle)
        return;

    introDuration--;
    if(introDuration <= 0)
    {
        introToggle = false;
        allObjects.player->enableComponent("PlayerMoveComp");
    }
}
