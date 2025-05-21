#include "bb10.hpp"

void StageBB10::load()
{
    //phase bools
    winstat = false;
    p4s1toggle = false;
    wavesSpawned = 0;
    phase1 = true;
    phase2 = false;
    phase3 = false;
    phase4 = false;
    phase2InitToggle = true;
    phase3InitToggle = true;
    phase4InitToggle = true;
    spawnCooldown = 10*60;
    spawnTimer = spawnCooldown/2;
    initSpawnerData();
    stopSpawning = false;

    //intro stuff
    introToggle = true;
    introDuration = 5*60;

    Text stagenum(bold, "BB-10", 70);
    stagenum.setPosition({TILESCALE*11, TILESCALE*8});
    stagenum.setFillColor(Color::White);
    texts.push_back(stagenum);

    Text title(bold, "Goodbye, Goodbye", 50);
    title.setPosition({TILESCALE*6, TILESCALE*12});
    title.setFillColor(Color::White);
    texts.push_back(title);

    Text op(regular, "OPERATION", 30);
    op.setPosition({TILESCALE*11+10, TILESCALE*6});
    op.setFillColor(Color::White);
    texts.push_back(op);

    Text tips(light, "Tips: ", 20);
    tips.setPosition({TILESCALE*7, TILESCALE*30});
    tips.setFillColor(Color::White);
    texts.push_back(tips);

    Text kings(light, "This should have been my burden", 20);
    kings.setPosition({TILESCALE*9, TILESCALE*30});
    kings.setFillColor(Color::Magenta);
    texts.push_back(kings);

    Text load(light, "Loading...", 20);
    load.setPosition({TILESCALE*25-10, TILESCALE*30});
    load.setFillColor(Color::White);
    texts.push_back(load);


    //stage stuff
    soundManager.addBGM("assets/The Opening.mp3", BGM);
    soundManager.playBGM(BGM);
    soundManager.addSFX("assets/jump.wav", JUMPSFX);
    soundManager.addSFX("assets/walking.wav", WALKINGSFX);
    soundManager.addSFX("assets/hammer_smash.ogg", ENEMYDEATH);

    allObjects.player->disableComponent("PlayerMoveComp");
    allObjects.player->disableComponent("SfxComp");
    allObjects.player->setTileXY(8, 13);
    allObjects.player->setHP(1);

    allObjects.peach = nullptr;

    Text ob(regular, "OBJECTIVE:", 20);
    ob.setPosition({TILESCALE*1, TILESCALE*1});
    ob.setFillColor(Color::White);
    objective.push_back(ob);

    Text reach(light, "Protect Amiya", 20);
    reach.setPosition({TILESCALE*2, TILESCALE*2});
    reach.setFillColor(Color::Blue);
    objective.push_back(reach);

    Text her(light, "Protect what you have left", 20);
    her.setPosition({TILESCALE*2, TILESCALE*3});
    her.setFillColor(Color::Red);
    objective.push_back(her);

    //amiya
    amiya = new GD_ModularObject("amiya", "assets/amiya_sprite.png", 10, 12);
    amiya->scaleObject(0.5);
    amiya->setHeight(TILESCALE*3);
    amiya->setWidth(TILESCALE);
    amiya->getSprite()->setPosition({TILESCALE*10, TILESCALE*11+2});
    allObjects.gameObjects.push_back(amiya);

    //red boxes
    for(int i = 0; i < 5; i++)
    {
        GD_ModularObject* box1 = new GD_ModularObject("redbox", "assets/red box.png", 0, 0);
        box1->scaleObject(1.3);
        box1->setHeight(TILESCALE*2);
        box1->setWidth(TILESCALE*2);
        if(box1->isVisible())
            box1->toggleVisibility();
        allObjects.gameObjects.push_back(box1);
        Boxes.push_back(box1);
    }
    //set pos for all boxes later
    Boxes.at(0).value()->getSprite()->setPosition({TILESCALE*7, TILESCALE*5});
    Boxes.at(0).value()->toggleVisibility();
    Boxes.at(1).value()->getSprite()->setPosition({TILESCALE*4, TILESCALE*16});
    //Boxes.at(1).value()->toggleVisibility();
    Boxes.at(2).value()->getSprite()->setPosition({TILESCALE*26, TILESCALE*20});
    //Boxes.at(2).value()->toggleVisibility();
    Boxes.at(3).value()->getSprite()->setPosition({TILESCALE*0, TILESCALE*28});
    //Boxes.at(3).value()->toggleVisibility();
    Boxes.at(4).value()->getSprite()->setPosition({TILESCALE*26, TILESCALE*28});
    //Boxes.at(4).value()->toggleVisibility();


    //1/3rds of phase 1 top plats 
    allObjects.Platforms.push_back(objectFactory.makePlatform(6, 7));
    allObjects.aboveLadder.push_back(allObjects.Platforms.back());
    allObjects.Platforms.push_back(objectFactory.makePlatform(7, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(8, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(9, 7));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(10, 7));
    allObjects.Platforms.back()->move(0, -PIXEL*2);
    allObjects.Platforms.push_back(objectFactory.makePlatform(11, 7));
    allObjects.Platforms.back()->move(0, -PIXEL*3);

    //2/3rds of phase 1 top plats
    allObjects.Platforms.push_back(objectFactory.makePlatform(12, 8));
    allObjects.Platforms.push_back(objectFactory.makePlatform(13, 8));
    allObjects.Platforms.push_back(objectFactory.makePlatform(14, 8));
    allObjects.Platforms.push_back(objectFactory.makePlatform(15, 8));
    allObjects.Platforms.push_back(objectFactory.makePlatform(16, 8));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(17, 8));
    allObjects.Platforms.back()->move(0, -PIXEL*2);

    //3/3rds of phase 1 top plats
    allObjects.Platforms.push_back(objectFactory.makePlatform(18, 9));
    allObjects.Platforms.push_back(objectFactory.makePlatform(19, 9));
    allObjects.Platforms.push_back(objectFactory.makePlatform(20, 9));
    allObjects.Platforms.push_back(objectFactory.makePlatform(21, 9));
    allObjects.Platforms.push_back(objectFactory.makePlatform(22, 9));
    allObjects.Platforms.push_back(objectFactory.makePlatform(23, 9));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(24, 9));
    allObjects.Platforms.back()->move(0, -PIXEL*2);

    //top left ladders
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 8));
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 9));
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 10));
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 11));
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 12));
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 13));

    //plats under those ladders
    allObjects.Platforms.push_back(objectFactory.makePlatform(5, 14));
    allObjects.Platforms.push_back(objectFactory.makePlatform(6, 14));
    allObjects.Platforms.push_back(objectFactory.makePlatform(7, 14));
    allObjects.Platforms.push_back(objectFactory.makePlatform(8, 14));
    allObjects.Platforms.push_back(objectFactory.makePlatform(9, 14));

    //plats under amiya in phase 1
    allObjects.Platforms.push_back(objectFactory.makePlatform(10, 14));
    phase1Plats.push_back(allObjects.Platforms.back());
    allObjects.Platforms.push_back(objectFactory.makePlatform(11, 14));
    phase1Plats.push_back(allObjects.Platforms.back());
    allObjects.Platforms.push_back(objectFactory.makePlatform(12, 14));
    phase1Plats.push_back(allObjects.Platforms.back());

    //bot right plats in phase 1
    //first 1/3rd
    allObjects.Platforms.push_back(objectFactory.makePlatform(13, 14));
    allObjects.aboveLadder.push_back(allObjects.Platforms.back());
    allObjects.Platforms.push_back(objectFactory.makePlatform(14, 14));
    allObjects.Platforms.push_back(objectFactory.makePlatform(15, 14));
    //2/3rds
    allObjects.Platforms.push_back(objectFactory.makePlatform(16, 13));
    allObjects.Platforms.back()->move(0, -PIXEL*2);
    allObjects.Platforms.push_back(objectFactory.makePlatform(17, 13));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(18, 13));
    allObjects.Platforms.push_back(objectFactory.makePlatform(19, 13));
    allObjects.Platforms.push_back(objectFactory.makePlatform(20, 13));
    allObjects.Platforms.push_back(objectFactory.makePlatform(21, 13));
    //3/3rds
    allObjects.Platforms.push_back(objectFactory.makePlatform(22, 12));
    allObjects.Platforms.back()->move(0, -PIXEL*2);
    allObjects.Platforms.push_back(objectFactory.makePlatform(23, 12));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(24, 12));
    allObjects.Platforms.push_back(objectFactory.makePlatform(25, 12));
    allObjects.Platforms.push_back(objectFactory.makePlatform(26, 12));
    allObjects.Platforms.push_back(objectFactory.makePlatform(27, 12));
    allObjects.platformEnds.push_back(allObjects.Platforms.back());

    //2nd ladders
    allObjects.ladders.push_back(objectFactory.makeLadder(13, 15));
    allObjects.ladders.push_back(objectFactory.makeLadder(13, 16));
    allObjects.ladders.push_back(objectFactory.makeLadder(13, 17));
    allObjects.ladders.push_back(objectFactory.makeLadder(13, 18));
    allObjects.ladders.push_back(objectFactory.makeLadder(13, 19));

    //top plats for 2nd phase
    //3/3rds
    allObjects.Platforms.push_back(objectFactory.makePlatform(12, 20));
    allObjects.Platforms.push_back(objectFactory.makePlatform(13, 20));
    allObjects.Platforms.push_back(objectFactory.makePlatform(14, 20));
    //2/3rds
    allObjects.Platforms.push_back(objectFactory.makePlatform(7, 19));
    allObjects.platformEnds.push_back(allObjects.Platforms.back());
    allObjects.Platforms.push_back(objectFactory.makePlatform(8, 19));
    allObjects.aboveLadder.push_back(allObjects.Platforms.back());
    allObjects.Platforms.push_back(objectFactory.makePlatform(9, 19));
    allObjects.Platforms.push_back(objectFactory.makePlatform(10, 19));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(11, 19));
    allObjects.Platforms.back()->move(0, -PIXEL*2);
    //1/3rds
    allObjects.Platforms.push_back(objectFactory.makePlatform(4, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(5, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(6, 18));
    allObjects.Platforms.back()->move(0, -PIXEL);

    //3rd ladder
    allObjects.ladders.push_back(objectFactory.makeLadder(8, 20));
    allObjects.ladders.push_back(objectFactory.makeLadder(8, 21));
    allObjects.ladders.push_back(objectFactory.makeLadder(8, 22));
    allObjects.ladders.push_back(objectFactory.makeLadder(8, 23));
    allObjects.ladders.push_back(objectFactory.makeLadder(8, 24));

    //plat under that ladder
    allObjects.Platforms.push_back(objectFactory.makePlatform(6, 25));
    allObjects.aboveLadder.push_back(allObjects.Platforms.back());
    allObjects.Platforms.push_back(objectFactory.makePlatform(7, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(8, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(9, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(10, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(11, 25));

    //plats under amiya 2nd phase   
    allObjects.Platforms.push_back(objectFactory.makePlatform(12, 25));
    phase2Plats.push_back(allObjects.Platforms.back());
    allObjects.Platforms.push_back(objectFactory.makePlatform(13, 25));
    phase2Plats.push_back(allObjects.Platforms.back());
    allObjects.Platforms.push_back(objectFactory.makePlatform(14, 25));
    phase2Plats.push_back(allObjects.Platforms.back());

    //right side plats in phase 2
    //1/4ths
    allObjects.Platforms.push_back(objectFactory.makePlatform(15, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(16, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(17, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(18, 25));
    allObjects.Platforms.push_back(objectFactory.makePlatform(19, 25));
    allObjects.platformEnds.push_back(allObjects.Platforms.back());
    //2/4ths
    allObjects.Platforms.push_back(objectFactory.makePlatform(20, 24));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(21, 24));
    //3/4ths
    allObjects.Platforms.push_back(objectFactory.makePlatform(22, 23));
    allObjects.Platforms.back()->move(0, -PIXEL*2);
    allObjects.Platforms.push_back(objectFactory.makePlatform(23, 23));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(24, 23));
    //4/4ths
    allObjects.Platforms.push_back(objectFactory.makePlatform(25, 22));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(26, 22));
    allObjects.Platforms.push_back(objectFactory.makePlatform(27, 22));

    //bot ladder
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 26));
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 27));
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 28));
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 29));
    allObjects.ladders.push_back(objectFactory.makeLadder(6, 30));

    //bot layer of plats
    for(int i = 4; i < 21; i++)
    {
        allObjects.Platforms.push_back(objectFactory.makePlatform(i, 31));
    }

    //bot left plats
    allObjects.Platforms.push_back(objectFactory.makePlatform(0, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(1, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(2, 30));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(3, 30));
    allObjects.Platforms.back()->move(0, -PIXEL*2);

    //bot right plats
    allObjects.Platforms.push_back(objectFactory.makePlatform(21, 31));
    allObjects.Platforms.back()->move(0, PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(22, 31));
    allObjects.Platforms.back()->move(0, PIXEL*2);
    allObjects.Platforms.push_back(objectFactory.makePlatform(23, 31));
    allObjects.Platforms.back()->move(0, PIXEL*3);
    allObjects.Platforms.push_back(objectFactory.makePlatform(24, 31));
    allObjects.Platforms.back()->move(0, PIXEL*4);
    allObjects.Platforms.push_back(objectFactory.makePlatform(25, 31));
    allObjects.Platforms.back()->move(0, PIXEL*5);
    allObjects.Platforms.push_back(objectFactory.makePlatform(26, 30));
    allObjects.Platforms.push_back(objectFactory.makePlatform(27, 30));

    //ropes for decoration
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(21, 10));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(21, 11));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(21, 12));

    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(14, 9));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(14, 10));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(14, 11));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(14, 12));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(14, 13));

    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(7, 15));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(7, 16));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(7, 17));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(7, 18));

    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 13));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 14));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 15));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 16));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 17));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 18));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 19));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 20));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 21));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(24, 22));

    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 14));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 15));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 16));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 17));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 18));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 19));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 20));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 21));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 22));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 23));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(17, 24));

    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(0, 31));
    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(2, 31));

    allObjects.gameObjects.push_back(objectFactory.makeSpawnerRope(27, 31));

    //theresa for phase 4
    GD_ModularObject* theresa = new GD_ModularObject("theresa", "assets/theresa sprite.png");
    theresa->scaleObject(0.2);
    theresa->setTileXY(14,27);
    theresa->move(0, -5);
    theresa->toggleVisibility();
    allObjects.gameObjects.push_back(theresa);

    GD_ModularObject* orb1 = new GD_ModularObject("orb", "assets/theresa_ball.png");
    orb1->toggleVisibility();
    orb1->scaleObject(0.2);
    orb1->attachComponent(new OrbitComp(orb1, TILESCALE*15, TILESCALE*29, TILESCALE*4, 0, 2, OrbitComp::direction::right));
    allObjects.gameObjects.push_back(orb1);

    GD_ModularObject* orb2 = new GD_ModularObject("orb", "assets/theresa_ball.png");
    orb2->toggleVisibility();
    orb2->scaleObject(0.2);
    orb2->attachComponent(new OrbitComp(orb2, TILESCALE*15, TILESCALE*29, TILESCALE*4, 90, 2, OrbitComp::direction::right));
    allObjects.gameObjects.push_back(orb2);

    GD_ModularObject* orb3 = new GD_ModularObject("orb", "assets/theresa_ball.png");
    orb3->toggleVisibility();
    orb3->scaleObject(0.2);
    orb3->attachComponent(new OrbitComp(orb3, TILESCALE*15, TILESCALE*29, TILESCALE*4, 180, 2, OrbitComp::direction::right));
    allObjects.gameObjects.push_back(orb3);

    GD_ModularObject* orb4 = new GD_ModularObject("orb", "assets/theresa_ball.png");
    orb4->toggleVisibility();
    orb4->scaleObject(0.2);
    orb4->attachComponent(new OrbitComp(orb4, TILESCALE*15, TILESCALE*29, TILESCALE*4, 270, 2, OrbitComp::direction::right));
    allObjects.gameObjects.push_back(orb4);
}

void StageBB10::unLoad()
{
    allObjects.player->collisions.collidingLadder = nullptr;
    allObjects.player->collisions.collidingPlatform = nullptr;
    delete allObjects.peach;
    allObjects.peach = nullptr;

    //puts all remaining fireballs back into the pool
    for(int i = 0; i < allObjects.enemies.size(); i++)
        if(allObjects.enemies.at(i)->getID() == FIREBALL)
        {
            fireballPool.releaseIntoPool(allObjects.enemies.at(i));
            allObjects.enemies.erase(allObjects.enemies.begin() + i);
        }

    for(int i = 0; i < allObjects.enemies.size(); i++)
        delete allObjects.enemies.at(i);

    for(int i = 0; i < allObjects.Platforms.size(); i++)
        delete allObjects.Platforms.at(i);

    //puts all remaining hammer items back into the pool
    for(int i = 0; i < allObjects.gameObjects.size(); i++)
        if(allObjects.gameObjects.at(i)->getID() == HAMMERITEM)
        {
            hammerPool.releaseIntoPool(allObjects.gameObjects.at(i));
            allObjects.gameObjects.erase(allObjects.gameObjects.begin() + i);
        }

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

    soundManager.reset();
    texts.clear();
    objective.clear();
    Boxes.clear();
    phase1Plats.clear();
    phase2Plats.clear();
    amiya = nullptr;
}

int StageBB10::update()
{
    intro();

    if(!introToggle)
    {
        checkPhaseTrans();
        spawnManager();
        updateSpawner(&spawner1);
        updateSpawner(&spawner2);
        updateSpawner(&spawner3);
        updateSpawner(&spawner4);
        updateSpawner(&spawner5);
    }

    int returnStatus = Scene::update();
    allObjects.player->update();
    allObjects.hammer->update();

    //kills enemies if touching theresa's orbs
    //ends game when touching amiya
    for(int i = 0; i < allObjects.enemies.size(); i++)
    {
        allObjects.enemies.at(i)->update();

        if(checkEnemyCollison(allObjects.enemies.at(i), amiya))
            return LOST;

        for(int k = 0; k < allObjects.gameObjects.size(); k++)
            if(allObjects.gameObjects.at(k)->getID() == "orb" && allObjects.gameObjects.at(k)->isVisible() && checkEnemyCollison(allObjects.enemies.at(i), allObjects.gameObjects.at(k)))
            {
                allObjects.enemies.at(i)->setHP(0);
                allObjects.enemies.at(i)->setDead(true);
                soundManager.playSFX(ENEMYDEATH, false);
            }
    }

    //updates orbs to rotate them
    for(int i = 0; i < allObjects.gameObjects.size(); i++)
        if(allObjects.gameObjects.at(i)->getID() == "orb")
            allObjects.gameObjects.at(i)->update();

    for(int i = 0; i < allObjects.Platforms.size(); i++)
        allObjects.Platforms.at(i)->update();

    //retruns enemies back into pool when theyve died 
    for(int i = 0; i < allObjects.enemies.size(); i++)
        if(allObjects.enemies.at(i)->getReturnToPool())
        {
            fireballPool.releaseIntoPool(allObjects.enemies.at(i));
            allObjects.enemies.erase(allObjects.enemies.begin() + i);
        }
    
    return returnStatus;
}

void StageBB10::draw(RenderWindow* window)
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

void StageBB10::intro()
{
    if(!introToggle)
        return;

    introDuration--;
    if(introDuration <= 0)
    {
        introToggle = false;
        allObjects.player->enableComponent("PlayerMoveComp");
        allObjects.player->enableComponent("SfxComp");
    }
}

//has the conditions for each phase transition and inits the new phase 
void StageBB10::checkPhaseTrans()
{
    //phase transitions 
    if(phase1 && !phase2 && !phase3 && !phase4 && wavesSpawned >= 2) 
    {
        stopSpawning = true;
        if(allObjects.enemies.size() <= 0)
        {
            phase2 = true;
            stopSpawning = false;
            wavesSpawned = 0;
            spawnCooldown = BASESPAWNRATE + 60;
            spawnTimer = spawnCooldown/2;
        }
    }
    else if(phase1 && phase2 && !phase3 && !phase4 && wavesSpawned >= 6) 
    {
        stopSpawning = true;
        if(allObjects.enemies.size() <= 0)
        {
            phase3 = true;
            stopSpawning = false;
            wavesSpawned = 0;
            spawnCooldown = BASESPAWNRATE + 60*2;
            spawnTimer = spawnCooldown/2;
        }
    }
    else if(phase1 && phase2 && phase3 && !phase4 && wavesSpawned >= 8) 
    {
        stopSpawning = true;
        if(allObjects.enemies.size() <= 0)
        {
            phase4 = true;
            stopSpawning = false;
            wavesSpawned = 0;
            spawnCooldown = 0;
            spawnTimer = 0;
            winstat = true;
        }
    }
    else if(phase1 && phase2 && phase3 && phase4 && wavesSpawned >= 25) 
    {
        stopSpawning = true;
        if(allObjects.enemies.size() <= 0)
        {
            winDelay--;
            if(winstat)
            {
                winDelay = 60*5;
                winstat = false;
            }
            else if(winDelay <= 0 && !winstat)
                winCondition = true;
        }
    }

    //initializes for new phases
    if(phase2 && phase2InitToggle)
    {
        phase2InitToggle = false;
        Boxes.at(1).value()->toggleVisibility();
        Boxes.at(2).value()->toggleVisibility();
        amiya->getSprite()->setPosition({TILESCALE*15, TILESCALE*22+2});

        for(int i = 0; i < phase1Plats.size(); i++)
            for(int k = 0; k < allObjects.Platforms.size(); k++)
                if(allObjects.Platforms.at(k) == phase1Plats.at(i))
                {
                    allObjects.Platforms.erase(allObjects.Platforms.begin() + k);
                    break;
                }
    }
    if(phase3 && phase3InitToggle)
    {
        phase3InitToggle = false;
        Boxes.at(3).value()->toggleVisibility();
        Boxes.at(4).value()->toggleVisibility();
        amiya->getSprite()->setPosition({TILESCALE*12, TILESCALE*28+2});

        for(int i = 0; i < phase2Plats.size(); i++)
            for(int k = 0; k < allObjects.Platforms.size(); k++)
                if(allObjects.Platforms.at(k) == phase2Plats.at(i))
                {
                    allObjects.Platforms.erase(allObjects.Platforms.begin() + k);
                    break;
                }
    }
    if(phase4 && phase4InitToggle)
    {
        phase4InitToggle = false;
        
        for(int i = 0; i < allObjects.gameObjects.size(); i++)
            if(allObjects.gameObjects.at(i)->getID() == "theresa" || allObjects.gameObjects.at(i)->getID() == "orb")
                allObjects.gameObjects.at(i)->toggleVisibility();
    }
}

//inits the struct data for the spawners
//its a func and not hard coded into load cuz i thought id change it mid run, but ig not
void StageBB10::initSpawnerData()
{
    spawner1.spawnX = TILESCALE*7 + TILESCALE/2;
    spawner1.SpawnY = TILESCALE*6;
    spawner1.maxEnemies = 6;
    spawner1.minEnemies = 4;
    spawner1.hammerSpawnX = 6*TILESCALE;
    spawner1.hammerSpawnY = 5*TILESCALE;
    spawner1.spawnInterval = 60*1.5;
    spawner1.spawnerTimer = 0;
    spawner1.isSpawning = false;
    spawner1.enemiesToSpawn = 0;
    spawner1.startDirection = RIGHT;

    spawner2.spawnX = TILESCALE*4 + TILESCALE/2;
    spawner2.SpawnY = TILESCALE*17;
    spawner2.maxEnemies = 5;
    spawner2.minEnemies = 3;
    spawner2.hammerSpawnX = 8*TILESCALE;
    spawner2.hammerSpawnY = 18*TILESCALE;
    spawner2.spawnInterval = 60*1;
    spawner2.spawnerTimer = 0;
    spawner2.isSpawning = false;
    spawner2.enemiesToSpawn = 0;
    spawner2.startDirection = RIGHT;

    spawner3.spawnX = TILESCALE*26 + TILESCALE/2;
    spawner3.SpawnY = TILESCALE*21;
    spawner3.maxEnemies = 4;
    spawner3.minEnemies = 2;
    spawner3.hammerSpawnX = 13*TILESCALE;
    spawner3.hammerSpawnY = 23*TILESCALE;
    spawner3.spawnInterval = 60*1;
    spawner3.spawnerTimer = 0;
    spawner3.isSpawning = false;
    spawner3.enemiesToSpawn = 0;
    spawner3.startDirection = LEFT;

    spawner4.spawnX = TILESCALE*0 + TILESCALE/2;
    spawner4.SpawnY = TILESCALE*29;
    spawner4.maxEnemies = 4;
    spawner4.minEnemies = 2;
    spawner4.hammerSpawnX = 10*TILESCALE;
    spawner4.hammerSpawnY = 29*TILESCALE;
    spawner4.spawnInterval = 60*1;
    spawner4.spawnerTimer = 0;
    spawner4.isSpawning = false;
    spawner4.enemiesToSpawn = 0;
    spawner4.startDirection = RIGHT;

    spawner5.spawnX = TILESCALE*26 + TILESCALE/2;
    spawner5.SpawnY = TILESCALE*29;
    spawner5.maxEnemies = 4;
    spawner5.minEnemies = 2;
    spawner5.hammerSpawnX = 17*TILESCALE;
    spawner5.hammerSpawnY = 29*TILESCALE;
    spawner5.spawnInterval = 60*1;
    spawner5.spawnerTimer = 0;
    spawner5.isSpawning = false;
    spawner5.enemiesToSpawn = 0;
    spawner5.startDirection = LEFT;
}

//manages all the spawners
//when randomly chosen if available in the current phase, the manager gives it enemies and adjusts the cooldown for the next spawner for balance 
//will also handle hammer spawns 
void StageBB10::spawnManager()
{
    spawnTimer++;
    if(spawnTimer >= spawnCooldown && !stopSpawning && !phase4)
    {
        spawnTimer = 0;
        bool loop = true;

        //loops if randnum doesnt give a valid number for that phase
        //ends loop after 10 tries to prevent crashing
        while(loop)
        {
            int randNum = rand() % 5 + 1;
            int loopBreak = -1;
            loopBreak++;
            if(loopBreak >= 10)
                break;

            if(phase1 && randNum == 1 && !spawner1.isSpawning)
            {
                //spawner 1
                spawner1.enemiesToSpawn = rand() % (spawner1.maxEnemies - spawner1.minEnemies) + spawner1.minEnemies;
                spawner1.spawnerTimer = spawner1.spawnInterval;
                spawnHammerItem(spawner1.hammerSpawnX, spawner1.hammerSpawnY);
                wavesSpawned++;
                loop = false;

                if(phase3 && !phase4)
                    spawnCooldown = BASESPAWNRATE + 4*60;
                else if(phase2 && !phase4)
                    spawnCooldown = BASESPAWNRATE + 5*60;
                else if(!phase4)
                    spawnCooldown = BASESPAWNRATE - 2*60;
            }
            if(phase2)
            {
                if(randNum == 2 && !spawner2.isSpawning)
                {
                    //spawner 2
                    spawner2.enemiesToSpawn = rand() % (spawner2.maxEnemies - spawner2.minEnemies) + spawner2.minEnemies;
                    spawner2.spawnerTimer = spawner2.spawnInterval;
                    spawnHammerItem(spawner2.hammerSpawnX, spawner2.hammerSpawnY);
                    wavesSpawned++;
                    loop = false;

                    if(phase3 && !phase4)
                        spawnCooldown = BASESPAWNRATE - 3*60;
                    else if(!phase4)
                        spawnCooldown = BASESPAWNRATE - 6*60;
                }
                if(randNum == 3 && !spawner3.isSpawning)
                {
                    //spawner 3
                    spawner3.enemiesToSpawn = rand() % (spawner3.maxEnemies - spawner3.minEnemies) + spawner3.minEnemies;
                    spawner3.spawnerTimer = spawner3.spawnInterval;
                    spawnHammerItem(spawner3.hammerSpawnX, spawner3.hammerSpawnY);
                    wavesSpawned++;
                    loop = false;

                    if(!phase4)
                        spawnCooldown = BASESPAWNRATE - 4*60;
                }
            }
            if(phase3)
            {
                if(randNum == 4 && !spawner4.isSpawning)
                {
                    //spawner 4
                    spawner4.enemiesToSpawn = rand() % (spawner4.maxEnemies - spawner4.minEnemies) + spawner4.minEnemies;
                    spawner4.spawnerTimer = spawner4.spawnInterval;
                    spawnHammerItem(spawner4.hammerSpawnX, spawner4.hammerSpawnY);
                    wavesSpawned++;
                    loop = false;

                    if(!phase4)
                        spawnCooldown = BASESPAWNRATE - 6*60;
                }
                if(randNum == 5 && !spawner5.isSpawning)
                {
                    //spawner 5
                    spawner5.enemiesToSpawn = rand() % (spawner5.maxEnemies - spawner5.minEnemies) + spawner5.minEnemies;
                    spawner5.spawnerTimer = spawner5.spawnInterval;
                    spawnHammerItem(spawner5.hammerSpawnX, spawner5.hammerSpawnY);
                    wavesSpawned++;
                    loop = false;

                    if(!phase4)
                        spawnCooldown = BASESPAWNRATE - 6*60;
                }
            }
            //phase 4 will be its own thing
        }
    }

    //phase 4 keeps spawning enemies besides spawner 1 since its so far away
    //phase 4 is just for visual effect
    else if(phase4 && !stopSpawning)
    {
        if(!p4s1toggle)
        {
            spawner1.enemiesToSpawn = spawner1.maxEnemies;
            spawner1.spawnerTimer = spawner1.spawnInterval;
            wavesSpawned++;
            p4s1toggle = true;
        }

        if(!spawner2.isSpawning)
        {
            spawner2.enemiesToSpawn = spawner2.maxEnemies;
            spawner2.spawnerTimer = spawner2.spawnInterval;
            wavesSpawned++;
        }
        if(!spawner3.isSpawning)
        {
            spawner3.enemiesToSpawn = spawner3.maxEnemies;
            spawner3.spawnerTimer = spawner3.spawnInterval;
            wavesSpawned++;
        }
        if(!spawner4.isSpawning)
        {
            spawner4.enemiesToSpawn = spawner4.maxEnemies;
            spawner4.spawnerTimer = spawner4.spawnInterval;
            wavesSpawned++;
        }
        if(!spawner5.isSpawning)
        {
            spawner5.enemiesToSpawn = spawner5.maxEnemies;
            spawner5.spawnerTimer = spawner5.spawnInterval;
            wavesSpawned++;
        }
    }
}

//only handles enemy spawns
//when spawner has enemies to spawn, spawns them at an interval until no more enemies are needed to be spawned 
void StageBB10::updateSpawner(BoxSpawner* spawner)
{
    if(spawner->enemiesToSpawn > 0)
    {
        spawner->isSpawning = true;
        spawner->spawnerTimer++;

        if(spawner->spawnerTimer >= spawner->spawnInterval)
            if(fireballPool.getAvailableSize() > 0)
            {
                spawner->enemiesToSpawn--;
                spawner->spawnerTimer = 0;
                allObjects.enemies.push_back(fireballPool.requestFromPool());
                allObjects.enemies.back()->getSprite()->setPosition({static_cast<float>(spawner->spawnX), static_cast<float>(spawner->SpawnY)});
                allObjects.enemies.back()->setMovingDirection(spawner->startDirection);
            }
    }
    else
    {
        spawner->isSpawning = false;
        spawner->spawnerTimer = spawner->spawnInterval;
    }
}

//spawns hammer items at a given location for that spawner
//unless theres alr a hammer item there
//getting a hammer item while alr having one just resets duration (hammerPowerComp)
void StageBB10::spawnHammerItem(int SpawnX, int SpawnY)
{
    float spawnX = SpawnX;
    float spawnY = SpawnY;

    for(int i = 0; i < allObjects.gameObjects.size(); i++)
        if(allObjects.gameObjects.at(i)->getSprite()->getPosition().x == spawnX && allObjects.gameObjects.at(i)->getSprite()->getPosition().y == spawnY)
            return;

    if(hammerPool.getAvailableSize() > 0)
    {
        allObjects.gameObjects.push_back(hammerPool.requestFromPool());
        allObjects.gameObjects.back()->getSprite()->setPosition({spawnX, spawnY});
    }
}