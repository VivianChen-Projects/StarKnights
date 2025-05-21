#include "levelSelect.hpp"

void LevelSelect::load()
{
    selected = 0;
    blinkTimer = 0;
    blinkWhite = true;
    selectCooldown = 20;

    for(int i = 0; i < NUMBEROFSTAGES; i++)
    {
        string temp;
        temp.assign("Level ");
        temp.append(to_string(i+1));

        Text gameTitle(font, temp, 15);
        gameTitle.setPosition({TILESCALE*3, TILESCALE * (3.0f*i+3)});
        gameTitle.setFillColor(Color::Red);
        texts.push_back(gameTitle);
    }
}

void LevelSelect::getInput()
{
    selectCooldown--;
    if(Keyboard::isKeyPressed(Keyboard::Scancode::W) && selectCooldown <= 0)
    {
        selectCooldown = 10;
        selected--;
        blinkWhite = true;
        if(selected <= -1)
            selected = NUMBEROFSTAGES-1;
    }

    if(Keyboard::isKeyPressed(Keyboard::Scancode::S) && selectCooldown <= 0)
    {
        selectCooldown = 10;
        selected++;
        blinkWhite = true;
        if(selected >= NUMBEROFSTAGES)
            selected = 0;
    }
}   

void LevelSelect::blinkButton(Text* button)
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

void LevelSelect::draw(RenderWindow* window)
{
    for(int i = 0; i < texts.size(); i++)
        window->draw(texts.at(i).value());
}

void LevelSelect::unLoad()
{
    texts.clear();
}

int LevelSelect::update()
{
    getInput();
    keepButtonsRed();
    blinkButton(&texts.at(selected).value());

    if(Keyboard::isKeyPressed(Keyboard::Scancode::Enter) && selectCooldown <= 0)
        return selected + 1;

    return ONGOING;
}

void LevelSelect::keepButtonsRed()
{
    for(int i = 0; i < texts.size(); i++)
        if(i != selected)
            texts.at(i).value().setFillColor(Color::Red);
}