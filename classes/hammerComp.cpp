#include "hammerComp.h"

//moves hammer along with mario and animates it
void HammerComp::perform(){

    GD_ModularObject* owner = getOwner();
    GD_ModularObject* parent = dynamic_cast<GD_ModularObject*>(owner->getParent());

    w = owner->getFrameW()/owner->getFrameX();
    h = owner->getFrameH()/owner->getFrameY();
    
    if(parent->collisions.smash){
        owner->toggleVisibility();
        if(parent->getFaceDirection() == RIGHT){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY();

            if(time > 0.0){
                parentX = parent->getSprite()->getPosition().x;
                parentY = parent->getSprite()->getPosition().y;

                owner->getSprite()->setPosition({parentX, parentY - TILESCALE});
                x = owner->getSpriteRecX();
                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                if(time > 0.2){
                    parentX = parent->getSprite()->getPosition().x;
                    parentY = parent->getSprite()->getPosition().y;

                    owner->getSprite()->setPosition({parentX + TILESCALE, parentY});
                    x = owner->getSpriteRecX()+ 16 ;
                    owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                }
                if(time > 0.3){
                    time = 0;
                    parent->collisions.smash = false;
                }
            }
        }
        else if (parent->getFaceDirection() == LEFT){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() + 16;

            if(time > 0.0){
                parentX = parent->getSprite()->getPosition().x;
                parentY = parent->getSprite()->getPosition().y;

                owner->getSprite()->setPosition({parentX, parentY - TILESCALE});
                x = owner->getSpriteRecX();
                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                if(time > 0.2){
                    parentX = parent->getSprite()->getPosition().x;
                    parentY = parent->getSprite()->getPosition().y;

                    owner->getSprite()->setPosition({parentX - TILESCALE, parentY});
                    x = owner->getSpriteRecX()+ 16 ;
                    owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                }
                if(time > 0.3){
                    time = 0;
                    parent->collisions.smash = false;
                }
            }
        }
        
    }

    else if(!parent->collisions.smash){
        if(owner->isVisible()){
            owner->toggleVisibility();
        }
    }
}
