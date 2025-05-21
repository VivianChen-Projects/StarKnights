#include "mainMenu.hpp"

void MainMenu::load()
{
    selected = 0;
    blinkTimer = 0;
    blinkWhite = true;
    selectCooldown = 20;

    Text gameTitle(font, "A Donkey Kong Remake", 30);
    gameTitle.setPosition({TILESCALE*2, TILESCALE*10});
    gameTitle.setFillColor(Color::Red);
    texts.push_back(gameTitle);

    Text authors(font, "Made by: Eric Franco and Vivian Chen", 15);
    authors.setPosition({TILESCALE*3-2, TILESCALE*12});
    authors.setFillColor(Color::Red);
    texts.push_back(authors);

    Text start(font, "start game", 15);
    start.setPosition({TILESCALE*10, TILESCALE*15});
    start.setFillColor(Color::Red);
    texts.push_back(start);

    Text settings(font, "settings", 15);
    settings.setPosition({TILESCALE*10+15, TILESCALE*17});
    settings.setFillColor(Color::Red);
    texts.push_back(settings);

    Text exit(font, "exit game", 15);
    exit.setPosition({TILESCALE*10+5, TILESCALE*19});
    exit.setFillColor(Color::Red);
    texts.push_back(exit);

    //extra stuff
    GD_ModularObject* gameLogo = new GD_ModularObject("gamelogo", "assets/gameLogo.png");
    gameLogo->getSprite()->setPosition({TILESCALE*2, TILESCALE*0.5});
    gameLogo->scaleObject(0.3);
    pics.push_back(gameLogo);

    Text taken(font, "Assets taken from:", 15);
    taken.setPosition({TILESCALE*8, TILESCALE*24});
    taken.setFillColor(Color::White);
    texts.push_back(taken);

    GD_ModularObject* aklogo = new GD_ModularObject("aklogo", "assets/Arknights_logo.png");
    aklogo->getSprite()->setPosition({TILESCALE*13, TILESCALE*27});
    aklogo->scaleObject(0.2);
    pics.push_back(aklogo);

    GD_ModularObject* hsrlogo = new GD_ModularObject("hsrlogo", "assets/HSR_logo.png");
    hsrlogo->getSprite()->setPosition({TILESCALE*1, TILESCALE*25});
    hsrlogo->scaleObject(0.2);
    pics.push_back(hsrlogo);
}

void MainMenu::getInput()
{
    selectCooldown--;
    if(Keyboard::isKeyPressed(Keyboard::Scancode::W) && selectCooldown <= 0)
    {
        selectCooldown = 10;
        selected--;
        blinkWhite = true;
        if(selected <= -1)
            selected = 2;
    }

    if(Keyboard::isKeyPressed(Keyboard::Scancode::S) && selectCooldown <= 0)
    {
        selectCooldown = 10;
        selected++;
        blinkWhite = true;
        if(selected >= 3)
            selected = 0;
    }
}   

void MainMenu::blinkButton(Text* button)
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

void MainMenu::draw(RenderWindow* window)
{
    for(int i = 0; i < texts.size(); i++)
        window->draw(texts.at(i).value());

    for(int i = 0; i < pics.size(); i++)
        pics.at(i).value()->draw(window);
}

void MainMenu::unLoad()
{
    texts.clear();

    for(int i = 0; i < pics.size(); i++)
        delete pics.at(i).value();
    pics.clear();
}

int MainMenu::update()
{
    getInput();
    keepButtonsRed();
    blinkButton(&texts.at(selected+2).value());

    if(Keyboard::isKeyPressed(Keyboard::Scancode::Enter) && selected == 0 && selectCooldown <= 0)
        return STARTGAME;
    if(Keyboard::isKeyPressed(Keyboard::Scancode::Enter) && selected == 1)
        return SETTINGS;
    if(Keyboard::isKeyPressed(Keyboard::Scancode::Enter) && selected == 2)
        return EXITGAME;

    return ONGOING;
}

void MainMenu::keepButtonsRed()
{
    for(int i = 2; i < texts.size() - 1; i++)
        if(i != selected + 2)
            texts.at(i).value().setFillColor(Color::Red);
}