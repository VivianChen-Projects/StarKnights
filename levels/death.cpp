#include "death.hpp"

void Death::load()
{
    selected = 0;
    blinkTimer = 0;
    blinkWhite = true;
    selectCooldown = 20;

    Text gameTitle(font, "you died!", 30);
    gameTitle.setPosition({TILESCALE*9, TILESCALE*8});
    gameTitle.setFillColor(Color::Red);
    texts.push_back(gameTitle);

    Text start(font, "restart stage?", 15);
    start.setPosition({TILESCALE*10, TILESCALE*13});
    start.setFillColor(Color::Red);
    texts.push_back(start);

    Text exit(font, "back to main menu", 15);
    exit.setPosition({TILESCALE*9, TILESCALE*15});
    exit.setFillColor(Color::Red);
    texts.push_back(exit);

}

void Death::getInput()
{
    selectCooldown--;
    if(Keyboard::isKeyPressed(Keyboard::Scancode::W) && selectCooldown <= 0)
    {
        selectCooldown = 10;
        selected--;
        blinkWhite = true;
        if(selected <= -1)
            selected = 1;
    }

    if(Keyboard::isKeyPressed(Keyboard::Scancode::S) && selectCooldown <= 0)
    {
        selectCooldown = 10;
        selected++;
        blinkWhite = true;
        if(selected >= 2)
            selected = 0;
    }
}   

void Death::blinkButton(Text* button)
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

void Death::draw(RenderWindow* window)
{
    for(int i = 0; i < texts.size(); i++)
        window->draw(texts.at(i).value());
}

void Death::unLoad()
{
    texts.clear();
}

int Death::update()
{
    getInput();
    keepButtonsRed();
    blinkButton(&texts.at(selected+1).value());

    if(Keyboard::isKeyPressed(Keyboard::Scancode::Enter) && selected == 0 && selectCooldown <= 0)
        return RESTART;
    if(Keyboard::isKeyPressed(Keyboard::Scancode::Enter) && selected == 1)
        return MAINMENU;

    return ONGOING;
}

void Death::keepButtonsRed()
{
    for(int i = 1; i < texts.size(); i++)
        if(i != selected)
            texts.at(i).value().setFillColor(Color::Red);
}