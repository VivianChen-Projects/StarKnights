#include "settings.hpp"

void Settings::load()
{
    selected = 0;
    blinkTimer = 0;
    blinkWhite = true;
    selectCooldown = 20;
    volumeSelectCooldown = 3;

    Text musicVol(font, "<- 100 ->", 15);
    musicVol.setPosition({TILESCALE*11, TILESCALE*12});
    musicVol.setFillColor(Color::Red);
    texts.push_back(musicVol);

    Text sfxvol(font, "<- 100 ->", 15);
    sfxvol.setPosition({TILESCALE*11, TILESCALE*17});
    sfxvol.setFillColor(Color::Red);
    texts.push_back(sfxvol);

    Text mainmenu(font, "Back to main menu", 15);
    mainmenu.setPosition({TILESCALE*9, TILESCALE*20});
    mainmenu.setFillColor(Color::Red);
    texts.push_back(mainmenu);

    Text title(font, "Settings", 20);
    title.setPosition({TILESCALE*11, TILESCALE*8});
    title.setFillColor(Color::Red);
    texts.push_back(title);

    Text musictitle(font, "Music", 15);
    musictitle.setPosition({TILESCALE*12+10, TILESCALE*10+10});
    musictitle.setFillColor(Color::Red);
    texts.push_back(musictitle);

    Text sfxtitle(font, "Sound effects", 15);
    sfxtitle.setPosition({TILESCALE*10, TILESCALE*15+10});
    sfxtitle.setFillColor(Color::Red);
    texts.push_back(sfxtitle);
}

void Settings::getInput()
{
    selectCooldown--;
    volumeSelectCooldown--;
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

    if(Keyboard::isKeyPressed(Keyboard::Scancode::A) && volumeSelectCooldown <= 0)
        if(selected == 0)
        {
            MusicVolume--;
            volumeSelectCooldown = 3;
            if(MusicVolume < 0)
                MusicVolume = 0;
        }
        else if(selected == 1)
        {
            SoundVolume--;
            volumeSelectCooldown = 3;
            if(SoundVolume < 0)
                SoundVolume = 0;
        }

    if(Keyboard::isKeyPressed(Keyboard::Scancode::D) && volumeSelectCooldown <= 0)
        if(selected == 0)
        {
            MusicVolume++;
            volumeSelectCooldown = 3;
            if(MusicVolume > 100)
                MusicVolume = 100;
        }
        else if(selected == 1)
        {
            SoundVolume++;
            volumeSelectCooldown = 3;
            if(SoundVolume > 100)
                SoundVolume = 100;
        }
}   

void Settings::blinkButton(Text* button)
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

void Settings::draw(RenderWindow* window)
{
    for(int i = 0; i < texts.size(); i++)
        window->draw(texts.at(i).value());
}

void Settings::unLoad()
{
    texts.clear();
}

int Settings::update()
{
    getInput();
    keepButtonsRed();
    blinkButton(&texts.at(selected).value());

    string temp;
    temp.assign("<- ");
    temp.append(to_string(MusicVolume));
    temp.append(" ->");
    texts.at(0).value().setString(temp);

    string temp2;
    temp2.assign("<- ");
    temp2.append(to_string(SoundVolume));
    temp2.append(" ->");
    texts.at(1).value().setString(temp2);


    if(Keyboard::isKeyPressed(Keyboard::Scancode::Enter) && selected == 2)
        return MAINMENU;

    return ONGOING;
}

void Settings::keepButtonsRed()
{
    for(int i = 0; i < texts.size(); i++)
        if(i != selected)
            texts.at(i).value().setFillColor(Color::Red);
}