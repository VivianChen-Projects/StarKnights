//use a tile system for the map
//24 x 24 size
//28 tiles across
//32 tiles high, not too sure on this number

#include "classes/sceneManager.hpp"
#include "levels/mainMenu.hpp"
#include "levels/levelSelect.hpp"
#include "levels/death.hpp"
#include "classes/Definitions.hpp"
#include "levels/settings.hpp"
#include "levels/14-21.hpp"
#include "levels/bb10.hpp"
#include "levels/HSR.h"
#include "stdlib.h"
#include "time.h"
#include "levels/winScreen.hpp"


//didnt make an engine class, main is the engine instead
int main()
{
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode({28*TILESCALE, 32*TILESCALE}), "StarKnights");
    window.setFramerateLimit(60);

    SceneManager sceneManager;

    HSR* hsr = new HSR;
    sceneManager.addScene(hsr);

    StageBB10* stageBB10 = new StageBB10();
    sceneManager.addScene(stageBB10);

    Stage1421* stage1421= new Stage1421();
    sceneManager.addScene(stage1421);

    MainMenu* mainMenu = new MainMenu();
    sceneManager.addMenu(mainMenu);
    sceneManager.init();

    LevelSelect* levelSelect = new LevelSelect();
    sceneManager.addLevelSelect(levelSelect);

    Death* death = new Death();
    sceneManager.addDeathScreen(death);

    Settings* settings = new Settings();
    sceneManager.addSettings(settings);

    WinScreen* win = new WinScreen();
    sceneManager.addWinScreen(win);

    int sceneStatus, stageIndex = 1; //stage index is the level number, starting with 1

    while (window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        sceneStatus = sceneManager.updateCurrentScene();

        //menu transitions
        if(sceneManager.getCurrentScene() == mainMenu && sceneStatus == STARTGAME)
            sceneManager.changeCurrentScene(SceneManager::Type::LevelSelect, 0); 
        else if(sceneManager.getCurrentScene() == mainMenu && sceneStatus == EXITGAME)
            window.close();
        else if(sceneManager.getCurrentScene() == mainMenu && sceneStatus == SETTINGS)
            sceneManager.changeCurrentScene(SceneManager::Type::Settings, 0); 

        //level select transitions
        else if(sceneManager.getCurrentScene() == levelSelect && sceneStatus != ONGOING)
        {
            sceneManager.changeCurrentScene(SceneManager::Type::NextLevel, sceneStatus); 
            stageIndex = sceneStatus;
        }

        //death screen transitions
        else if(sceneManager.getCurrentScene() == death && sceneStatus == RESTART)
            sceneManager.changeCurrentScene(SceneManager::Type::NextLevel, stageIndex); 
        else if(sceneManager.getCurrentScene() == death && sceneStatus == MAINMENU)
            sceneManager.changeCurrentScene(SceneManager::Type::MainMenu, 0); 

        //settings transitions
        else if(sceneManager.getCurrentScene() == settings && sceneStatus == MAINMENU)
            sceneManager.changeCurrentScene(SceneManager::Type::MainMenu, 0); 

        //when dying in any stage, manually add stage here
        else if((sceneManager.getCurrentScene() == hsr || sceneManager.getCurrentScene() == stage1421 || sceneManager.getCurrentScene() == stageBB10) && sceneStatus == LOST)
            sceneManager.changeCurrentScene(SceneManager::Type::DeathScreen, 0); 

        //when winning in any stage, manually add stage here
        else if((sceneManager.getCurrentScene() == hsr || sceneManager.getCurrentScene() == stage1421 || sceneManager.getCurrentScene() == stageBB10) && sceneStatus == WIN)
            sceneManager.changeCurrentScene(SceneManager::Type::WinScreen, 0); 

        //win screen transitions 
        else if(sceneManager.getCurrentScene() == win && sceneStatus == MAINMENU)
            sceneManager.changeCurrentScene(SceneManager::Type::MainMenu, 0);
            
        if(sceneStatus == ONGOING)
            sceneManager.drawCurrentScene(&window);
        window.display();
    }

    sceneManager.unloadCurrentScene();
    delete hsr;
    delete stage1421;
    delete stageBB10;
    delete mainMenu;
    delete levelSelect;
    delete death;
    delete settings;


    return 0;
}