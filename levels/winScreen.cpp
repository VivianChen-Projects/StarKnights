#include "winScreen.hpp"

void WinScreen::load()
{
    blinkTimer = 0;
    blinkWhite = true;

    Text gameTitle(font, "you win!", 30);
    gameTitle.setPosition({TILESCALE*9, TILESCALE*8});
    gameTitle.setFillColor(Color::Red);
    texts.push_back(gameTitle);

    Text exit(font, "back to main menu", 15);
    exit.setPosition({TILESCALE*9, TILESCALE*13});
    exit.setFillColor(Color::Red);
    texts.push_back(exit);

}

void WinScreen::blinkButton(Text* button)
{
    blinkTimer--;
    if(blinkTimer <= 0)
    {
        blinkTimer = 30;
        blinkWhite = !blinkWhite;
    }

    if(blinkWhite)
        button->setFillColor(Color::White);
    else
        button->setFillColor(Color::Red);
}

void WinScreen::draw(RenderWindow* window)
{
    for(int i = 0; i < texts.size(); i++)
        window->draw(texts.at(i).value());
}

void WinScreen::unLoad()
{
    texts.clear();
}

int WinScreen::update()
{
    blinkButton(&texts.at(1).value());

    if(Keyboard::isKeyPressed(Keyboard::Scancode::Enter))
        return MAINMENU;

    return ONGOING;
}