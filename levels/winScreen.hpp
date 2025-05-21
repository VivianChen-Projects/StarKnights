#pragma once

#include "../classes/Scene.hpp"

class WinScreen: public Scene
{
    private:
        Font font;
        vector<optional<Text>> texts;
        int blinkTimer = 0;
        bool blinkWhite = true;

        void blinkButton(Text* button);
        void keepButtonsRed();

    public:
        WinScreen()
        {
            if(!font.openFromFile("assets/DK_Font.ttf"));
                return;
        }
        void load() override;
        void unLoad() override;
        int update() override;
        void draw(RenderWindow* window) override;

};