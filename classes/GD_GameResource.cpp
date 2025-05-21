#include "GD_GameResource.h"

//removed the atlas functionality

GD_GameResource* GD_GameResource::myInstance = nullptr;

GD_GameResource::GD_GameResource(){
}

GD_GameResource* GD_GameResource::createInstance(){
    if(myInstance == nullptr)
        myInstance = new GD_GameResource();
    return myInstance;
}

sf::Texture* GD_GameResource::getTexture(){
    return &texture;
}
sf::Font* GD_GameResource::getFont(){
    return &font;
}
