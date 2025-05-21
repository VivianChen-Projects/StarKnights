#pragma once

#include "../classes/Scene.hpp"

class Death: public Scene
{
    private:
        Font font;
        vector<optional<Text>> texts;
        int selected = 0;
        int blinkTimer = 0;
        bool blinkWhite = true;
        int selectCooldown = 0;

        void blinkButton(Text* button);
        void keepButtonsRed();
        void getInput();

    public:
        Death()
        {
            if(!font.openFromFile("assets/DK_Font.ttf"));
                return;
        }
        void load() override;
        void unLoad() override;
        int update() override;
        void draw(RenderWindow* window) override;

};