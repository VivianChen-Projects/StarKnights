#pragma once

#include "Scene.hpp"

using namespace std;
using namespace sf;

//keeps all scenes and loads/unloads them
class SceneManager
{
    private:
        vector<Scene*> scenes;
        Scene* mainMenu;
        Scene* deathScreen;
        Scene* settings;
        Scene* levelSelect;
        Scene* currentScene;
        Scene* winScreen;

    public:
        enum Type{MainMenu, DeathScreen, Settings, LevelSelect, NextLevel, WinScreen};
        void addScene(Scene* newScene);
        void addMenu(Scene* newMenu);
        void addDeathScreen(Scene* newDeathScreen);
        void addSettings(Scene* newSettings);
        void addLevelSelect(Scene* newLevelSelect);
        void addWinScreen(Scene* newWinScreen);
        void changeCurrentScene(Type type, int levelNumber);
        void loadCurrentScene();
        int updateCurrentScene();
        void drawCurrentScene(RenderWindow* Window);
        void unloadCurrentScene();
        Scene* getCurrentScene();
        void init();

};