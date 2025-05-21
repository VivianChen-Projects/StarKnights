#include "14-21.hpp"

void Stage1421::load()
{
    //intro stuff
    introToggle = true;
    introDuration = 500;

    Text stagenum(bold, "14-21", 70);
    stagenum.setPosition({TILESCALE*11, TILESCALE*8});
    stagenum.setFillColor(Color::White);
    texts.push_back(stagenum);

    Text title(bold, "The Myriad Dreams", 50);
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

    Text kings(light, "Only a King can confront another King", 20);
    kings.setPosition({TILESCALE*9, TILESCALE*30});
    kings.setFillColor(Color::Red);
    texts.push_back(kings);

    Text load(light, "Loading...", 20);
    load.setPosition({TILESCALE*25-10, TILESCALE*30});
    load.setFillColor(Color::White);
    texts.push_back(load);


    //stage stuff
    soundManager.addBGM("assets/ratio ultima.mp3", BGM);
    soundManager.playBGM(BGM);
    soundManager.addSFX("assets/jump.wav", JUMPSFX);
    soundManager.addSFX("assets/walking.wav", WALKINGSFX);

    allObjects.player = objectFactory.makePlayer(22, 6);
    allObjects.player->attachComponent(new SfxComp(allObjects.player, &soundManager));
    allObjects.hammer = objectFactory.makeHammer(allObjects.player);
    allObjects.player->disableComponent("PlayerMoveComp");

    Text ob(regular, "OBJECTIVE:", 20);
    ob.setPosition({TILESCALE*1, TILESCALE*1});
    ob.setFillColor(Color::White);
    objective.push_back(ob);

    Text reach(light, "Reach the Blue Objective Point", 20);
    reach.setPosition({TILESCALE*2, TILESCALE*2});
    reach.setFillColor(Color::Blue);
    objective.push_back(reach);

    Text her(light, "Get past Her Highness", 20);
    her.setPosition({TILESCALE*2, TILESCALE*3});
    her.setFillColor(Color::Red);
    objective.push_back(her);

    GD_ModularObject* box1 = new GD_ModularObject("bluebox1", "assets/blue box.png", 0, 0);
    box1->scaleObject(1.3);
    box1->getSprite()->setPosition({TILESCALE*13, TILESCALE*22});
    box1->setHeight(TILESCALE*2);
    box1->setWidth(TILESCALE*2);
    if(!box1->isVisible())
        box1->toggleVisibility();
    allObjects.gameObjects.push_back(box1);
    Box1 = box1;

    GD_ModularObject* box2 = new GD_ModularObject("bluebox2", "assets/blue box.png", 0, 0);
    box2->scaleObject(1.3);
    box2->getSprite()->setPosition({TILESCALE*3, TILESCALE*5});
    box2->setHeight(TILESCALE*2);
    box2->setWidth(TILESCALE*2);
    if(box2->isVisible())
        box2->toggleVisibility();
    allObjects.gameObjects.push_back(box2);
    Box2 = box2;

    allObjects.peach = nullptr;


    //platfrom player spawns on
    allObjects.Platforms.push_back(objectFactory.makePlatform(21, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(22, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(23, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(26, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(27, 7));

    //moving plats on the right
    platSpawnerManager.giveScenePlatformsVector(&allObjects.Platforms);
    platSpawnerManager.giveScenePlayer(allObjects.player);
    platSpawnerManager.makeNewSpawner(1, 3, 27, PlatSpawnerManager::Direction::up, 24, 33);

    //plats above theresa
    allObjects.Platforms.push_back(objectFactory.makePlatform(18, 9));
    allObjects.aboveLadder.push_back(objectFactory.makePlatform(17, 9));
    allObjects.Platforms.push_back(objectFactory.makePlatform(16, 9));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(15, 9));
    allObjects.Platforms.back()->move(0, -PIXEL*2);
    allObjects.Platforms.push_back(objectFactory.makePlatform(14, 9));
    allObjects.Platforms.back()->move(0, -PIXEL*3);
    allObjects.Platforms.push_back(objectFactory.makePlatform(13, 9));
    allObjects.Platforms.back()->move(0, -PIXEL*3);
    allObjects.Platforms.push_back(objectFactory.makePlatform(12, 9));
    allObjects.Platforms.back()->move(0, -PIXEL*2);
    allObjects.Platforms.push_back(objectFactory.makePlatform(11, 9));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.aboveLadder.push_back(objectFactory.makePlatform(10, 9));
    allObjects.Platforms.push_back(objectFactory.makePlatform(9, 9));

    //plat under 2nd flag
    allObjects.Platforms.push_back(objectFactory.makePlatform(6, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(5, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(4, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(3, 7));
    allObjects.Platforms.push_back(objectFactory.makePlatform(2, 7));

    //right ladders
    allObjects.ladders.push_back(objectFactory.makeLadder(17, 10));
    allObjects.ladders.push_back(objectFactory.makeLadder(17, 11));
    allObjects.ladders.push_back(objectFactory.makeLadder(17, 12));
    allObjects.ladders.push_back(objectFactory.makeLadder(17, 13));
    allObjects.ladders.push_back(objectFactory.makeLadder(17, 14));
    allObjects.ladders.push_back(objectFactory.makeLadder(17, 15));
    allObjects.ladders.push_back(objectFactory.makeLadder(17, 16));
    allObjects.ladders.push_back(objectFactory.makeLadder(17, 17));

    //left ladders
    allObjects.ladders.push_back(objectFactory.makeLadder(10, 10));
    allObjects.ladders.push_back(objectFactory.makeLadder(10, 11));
    allObjects.ladders.push_back(objectFactory.makeLadder(10, 12));
    allObjects.ladders.push_back(objectFactory.makeLadder(10, 13));
    allObjects.ladders.push_back(objectFactory.makeLadder(10, 14));
    allObjects.ladders.push_back(objectFactory.makeLadder(10, 15));
    allObjects.ladders.push_back(objectFactory.makeLadder(10, 16));
    allObjects.ladders.push_back(objectFactory.makeLadder(10, 17));

    //plats under left ladder
    allObjects.Platforms.push_back(objectFactory.makePlatform(7, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(8, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(9, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(10, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(11, 18));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(12, 18));
    allObjects.Platforms.back()->move(0, -PIXEL*2);

    //plats under right ladder
    allObjects.Platforms.push_back(objectFactory.makePlatform(20, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(19, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(18, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(17, 18));
    allObjects.Platforms.push_back(objectFactory.makePlatform(16, 18));
    allObjects.Platforms.back()->move(0, -PIXEL);
    allObjects.Platforms.push_back(objectFactory.makePlatform(15, 18));
    allObjects.Platforms.back()->move(0, -PIXEL*2);

    //theresa and her platform
    allObjects.Platforms.push_back(objectFactory.makePlatform(14, 15));
    allObjects.Platforms.push_back(objectFactory.makePlatform(13, 15));
    GD_ModularObject* theresa = new GD_ModularObject("theresa", "assets/theresa sprite.png");
    theresa->scaleObject(0.2);
    theresa->setTileXY(13,11);
    theresa->move(0, -5);
    allObjects.gameObjects.push_back(theresa);

    //plat for first flag
    allObjects.Platforms.push_back(objectFactory.makePlatform(13, 24));
    allObjects.Platforms.push_back(objectFactory.makePlatform(14, 24));

    //moving bot plat 
    allObjects.Platforms.push_back(objectFactory.makePlatform(7, 29));
    allObjects.Platforms.back()->attachComponent(new MovingPlatComp(allObjects.Platforms.back(), 1, MovingPlatComp::Direction::right, 11, allObjects.player));
    allObjects.Platforms.push_back(objectFactory.makePlatform(8, 29));
    allObjects.Platforms.back()->attachComponent(new MovingPlatComp(allObjects.Platforms.back(), 1, MovingPlatComp::Direction::right, 11, allObjects.player));
    allObjects.Platforms.push_back(objectFactory.makePlatform(9, 29));
    allObjects.Platforms.back()->attachComponent(new MovingPlatComp(allObjects.Platforms.back(), 1, MovingPlatComp::Direction::right, 11, allObjects.player));
    allObjects.Platforms.push_back(objectFactory.makePlatform(10, 29));
    allObjects.Platforms.back()->attachComponent(new MovingPlatComp(allObjects.Platforms.back(), 1, MovingPlatComp::Direction::right, 11, allObjects.player));

    //bot left plat
    allObjects.Platforms.push_back(objectFactory.makePlatform(4, 28));
    allObjects.Platforms.back()->move(0, -PIXEL*1);
    allObjects.Platforms.push_back(objectFactory.makePlatform(3, 28));
    allObjects.Platforms.push_back(objectFactory.makePlatform(2, 28));

    //left ladder
    for(int i = 0; i < 17; i++)
        allObjects.ladders.push_back(objectFactory.makeLadder(2, 27-i));

    //top right plat for the ladder
    allObjects.aboveLadder.push_back(objectFactory.makePlatform(2, 10));
    allObjects.Platforms.push_back(objectFactory.makePlatform(3, 10));
    allObjects.Platforms.back()->move(0, -PIXEL*1);
    allObjects.Platforms.push_back(objectFactory.makePlatform(4, 10));
    allObjects.Platforms.back()->move(0, -PIXEL*2);

    //fake ladder
    allObjects.gameObjects.push_back(objectFactory.makeLadder(2, 8));

    //theresa's orbs
    for(int i = 0; i < 8; i++)
    {
        GD_ModularObject* neworb = new GD_ModularObject("orb", "assets/theresa_ball.png");
        
        if(i >= 4)
        {
            neworb->toggleVisibility();
            neworb->scaleObject(0.2);
        }
        else
            neworb->scaleObject(0.15);

        allObjects.enemies.push_back(neworb);
    }
    float orbrotatespeed = 1;
    //first 4
    allObjects.enemies.at(0)->attachComponent(new OrbitComp(allObjects.enemies.at(0), TILESCALE*14, TILESCALE*13, TILESCALE*4, 0, orbrotatespeed+0.9, OrbitComp::direction::left));
    allObjects.enemies.at(1)->attachComponent(new OrbitComp(allObjects.enemies.at(1), TILESCALE*14, TILESCALE*13, TILESCALE*4, 90, orbrotatespeed+0.9, OrbitComp::direction::left));
    allObjects.enemies.at(2)->attachComponent(new OrbitComp(allObjects.enemies.at(2), TILESCALE*14, TILESCALE*13, TILESCALE*4, 180, orbrotatespeed+0.9, OrbitComp::direction::left));
    allObjects.enemies.at(3)->attachComponent(new OrbitComp(allObjects.enemies.at(3), TILESCALE*14, TILESCALE*13, TILESCALE*4, 270, orbrotatespeed+0.9, OrbitComp::direction::left));
    //second 4
    allObjects.enemies.at(4)->attachComponent(new OrbitComp(allObjects.enemies.at(4), TILESCALE*14, TILESCALE*13, TILESCALE*12, 0, orbrotatespeed-0.2, OrbitComp::direction::right));
    allObjects.enemies.at(5)->attachComponent(new OrbitComp(allObjects.enemies.at(5), TILESCALE*14, TILESCALE*13, TILESCALE*12, 90, orbrotatespeed-0.2, OrbitComp::direction::right));
    allObjects.enemies.at(6)->attachComponent(new OrbitComp(allObjects.enemies.at(6), TILESCALE*14, TILESCALE*13, TILESCALE*12, 180, orbrotatespeed-0.2, OrbitComp::direction::right));
    allObjects.enemies.at(7)->attachComponent(new OrbitComp(allObjects.enemies.at(7), TILESCALE*14, TILESCALE*13, TILESCALE*12, 270, orbrotatespeed-0.2, OrbitComp::direction::right));
}

void Stage1421::unLoad()
{
    Scene::unLoad();
    platSpawnerManager.reset();
    soundManager.reset();
    texts.clear();
    objective.clear();
    Box1 = nullptr;
    Box2 = nullptr;
}

int Stage1421::update()
{
    intro();

    int returnStatus = Scene::update();
    allObjects.player->update();
    allObjects.hammer->update();

    for(int i = 0; i < allObjects.enemies.size(); i++)
        allObjects.enemies.at(i)->update();

    for(int i = 0; i < allObjects.Platforms.size(); i++)
        allObjects.Platforms.at(i)->update();

    platSpawnerManager.update();

    //to toggle the blue boxes
    boxCooldow--;
    if(Box1.value()->isVisible() && checkEnemyCollison(allObjects.player, Box1.value()))
    {
        Box1.value()->toggleVisibility();
        Box2.value()->toggleVisibility();
        boxCooldow = 20;

        for(int i = 4; i < allObjects.enemies.size(); i++)
            allObjects.enemies.at(i)->toggleVisibility();
    }
    if(Box2.value()->isVisible() && checkEnemyCollison(allObjects.player, Box2.value()) && boxCooldow <= 0)
    {
        return WIN;
    }

    return returnStatus;
}

void Stage1421::draw(RenderWindow* window)
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

void Stage1421::intro()
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