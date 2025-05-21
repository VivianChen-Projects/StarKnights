#pragma once

#include "../classes/Scene.hpp"

class MainMenu: public Scene
{
    private:
        Font font;
        vector<optional<Text>> texts;
        vector<optional<GD_ModularObject*>> pics;
        int selected = 0;
        int blinkTimer = 0;
        bool blinkWhite = true;
        int selectCooldown = 0;

        void blinkButton(Text* button);
        void keepButtonsRed();
        void getInput();

    public:
        MainMenu()
        {
            if(!font.openFromFile("assets/DK_Font.ttf"));
                return;
        }
        void load() override;
        void unLoad() override;
        int update() override;
        void draw(RenderWindow* window) override;

};