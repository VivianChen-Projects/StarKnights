#include "sceneManager.hpp"

//keeps all scenes and loads/unloads them

void SceneManager::addScene(Scene* newScene)
{
    scenes.push_back(newScene);
}

void SceneManager::addMenu(Scene* newMenu)
{
    mainMenu = newMenu;
}

void SceneManager::addDeathScreen(Scene* newDeathScreen)
{
    deathScreen = newDeathScreen;
}

void SceneManager::addLevelSelect(Scene* newLevelSelect)
{
    levelSelect = newLevelSelect;
}

void SceneManager::addSettings(Scene* newSettings)
{
    settings = newSettings;
}

void SceneManager::addWinScreen(Scene* newWinScreen)
{
    winScreen = newWinScreen;
}

void SceneManager::changeCurrentScene(Type type, int levelNumber)
{
    unloadCurrentScene();

    if(type == NextLevel)
        currentScene = scenes.at(levelNumber-1);
    else if(type == MainMenu) 
        currentScene = mainMenu;
    else if(type == DeathScreen) 
        currentScene = deathScreen;
    else if(type == Settings) 
        currentScene = settings;
    else if(type == LevelSelect) 
        currentScene = levelSelect;
    else if(type == WinScreen)
        currentScene = winScreen;

    loadCurrentScene();
}

void SceneManager::loadCurrentScene()
{
    currentScene->load();
}

int SceneManager::updateCurrentScene()
{
    return currentScene->update();
}

void SceneManager::drawCurrentScene(RenderWindow* window)
{
    currentScene->draw(window);
}

void SceneManager::unloadCurrentScene()
{
    currentScene->unLoad();
}

Scene* SceneManager::getCurrentScene()
{
    return currentScene;
}

void SceneManager::init()
{
    currentScene = mainMenu;
    loadCurrentScene();
}