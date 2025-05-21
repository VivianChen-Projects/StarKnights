#include "spriteComp.h"

//handles sprite animations 
//properly kills enemies when thier death animation finishes
void SpriteComp::perform(){
    if(!getEnabled())
        return;

    GD_ModularObject* owner = getOwner();

    w = owner->getFrameW()/owner->getFrameX();
    h = owner->getFrameH()/owner->getFrameY();

    //Player animation
    if (owner->getID() == PLAYER){
        //walking right
        if(owner->collisions.walkRight){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY();

            if(counter < 4 && time > 0.3){
                x = owner->getSpriteRecX()+ counter * 16 ;
                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                counter ++;
                if(counter == 4)
                    counter = 1;
                time = 0;
                deltaTime = clock.restart().asSeconds();
            }
            else if(counter == 4 && time > 0.3){
                counter = 0;
            }
            prevState = WALK_R;
            approachingLadder = WALK_R;
        }
        //walking left
        else if(owner->collisions.walkLeft){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() + 16;

            if(counter < 4 && time > 0.3){
                x = owner->getSpriteRecX()+ counter * 16 ;

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                counter ++;
                time = 0;
                deltaTime = clock.restart().asSeconds();
            }
            else if(counter == 4){
                counter = 0;
            }
            prevState = WALK_L;
            approachingLadder = WALK_L;
        }
        //climbing
        else if(owner->collisions.climbing){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() + (2 * 16);

            if(counter < 2 && time > 0.3){
                x = owner->getSpriteRecX()+ counter * 16 ;

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                counter ++;
                time = 0;
                deltaTime = clock.restart().asSeconds();
            }
            else if(counter == 2){
                counter = 0;
            }
            prevState = CLIMBING;
        }
        //animation stop (setting face direction)
        else if (!owner->collisions.walkLeft && !owner->collisions.walkRight && !owner->collisions.climbing){
            if(prevState == DEFAULT_R){
                x = owner->getSpriteRecX();
                y = owner->getSpriteRecY();

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                prevState = NONE;
                counter = 0;
                time = 0;
            }
            else if(prevState == DEFAULT_L){
                x = owner->getSpriteRecX();
                y = owner->getSpriteRecY() + 16;

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                prevState = NONE;
                counter = 0;
                time = 0;
            }
            else if (prevState == WALK_R){
                x = owner->getSpriteRecX()+ 4 * 16 ;
                y = owner->getSpriteRecY();

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));

                prevState = DEFAULT_R;
            }
            else if (prevState == WALK_L){
                x = owner->getSpriteRecX()+ 4 * 16 ;
                y = owner->getSpriteRecY() + 16;

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));

                prevState = DEFAULT_L;
            }
            else if (prevState == CLIMBING){ 
                if(approachingLadder == WALK_L)
                    prevState = DEFAULT_L;
                else if (approachingLadder == WALK_R)
                    prevState = DEFAULT_R;
                approachingLadder = NONE;
            }
            
        }

    }
    //dk animation
    else if(owner->getID() == ENEMY){
        //idle
        if(owner->getState() == IDLE){ //temporary, will fix once enemy comp is finish 
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() ;

            if(counter < 4 && time > 0.3){
                x = owner->getSpriteRecX()+ counter * 48 ;

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                counter ++;
                time = 0;
                deltaTime = clock.restart().asSeconds();
            }
            else if(counter == 4){
                counter = 0;
            }
        }
        //throwing barrel down
        else if(owner->getState() == THROW_BARREL_D){ //temporary, will fix once enemy comp is finish 
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY()+32;

            if(time > 4){
                x = owner->getSpriteRecX();

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                if(time >4.2){
                    time = 0;
                    deltaTime = clock.restart().asSeconds();
                    y = owner->getSpriteRecY();
                    owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                }
            }
        }
        //throwing barrel left
        else if(owner->getState() == THROW_BARREL_L){ //temporary, will fix once enemy comp is finish 
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY()+(2 * 32);

            if(time > 4){
                x = owner->getSpriteRecX();

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                if(time >4.2){
                    time = 0;
                    deltaTime = clock.restart().asSeconds();
                    y = owner->getSpriteRecY();
                    owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                }
            }
        }
        //throwing barrel right
        else if(owner->getState() == THROW_BARREL_R){ //temporary, will fix once enemy comp is finish 
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY()+(3 * 32);

            if(time > 4){
                x = owner->getSpriteRecX();

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                if(time >4.2){
                    time = 0;
                    deltaTime = clock.restart().asSeconds();
                    y = owner->getSpriteRecY();
                    owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                }
            }
        }
    }
    //fireball animation
    else if(owner->getID() == FIREBALL){
        //if dead play dead animation
        if(owner->getHP() <= 0){
            if(!killed){
                killed = true;
                counter = 0;
                owner->disableComponent("EnemyComp");
            }
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() + (2 * 16);

            if(counter < 4 && time > 0.3){
                x = owner->getSpriteRecX()+ (counter * 16 );

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                time = 0;
                counter++;
                deltaTime = clock.restart().asSeconds();
                
            }
            else if(counter >= 4)
            {
                owner->toggleVisibility();
                setEnabled(false);
                owner->setReturnToPool(true);
                killed = false;
                counter = 0;
            }
        }
        //if not dead 

        //walking left
        else if(owner->getMovingDirection()==LEFT){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() + 16;

            if(counter < 2 && time > 0.3){
                x = owner->getSpriteRecX()+ (counter * 16) ;

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                counter ++;
                time = 0;
                deltaTime = clock.restart().asSeconds();
            }
            else if(counter == 2){
                counter = 0;
            }
        }
        //walking right
        else if(owner->getMovingDirection()==RIGHT){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY();

            if(counter < 2 && time > 0.3){
                x = owner->getSpriteRecX()+ (counter * 16 );

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                counter ++;
                time = 0;
                deltaTime = clock.restart().asSeconds();
            }
            else if(counter == 2){
                counter = 0;
            }
        }
        
    }
    //barrel animation
    else if(owner->getID() == BARREL){
        //if dead play dead animation
        if(owner->getHP() <= 0){
            if(!killed){
                killed = true;
                counter = 0;
                owner->disableComponent("EnemyComp");
            }
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() + (3 * 16);

            if(counter < 4 && time > 0.3){
                x = owner->getSpriteRecX()+ (counter * 16 );

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                time = 0;
                counter++;
                deltaTime = clock.restart().asSeconds();
                
            }
            else if(counter >= 4)
            {
                owner->toggleVisibility();
                setEnabled(false);
                owner->setReturnToPool(true);
                killed = false;
                counter = 0;
            }
        }
        //if not dead 

        //falling animation
        else if(!owner->collisions.floor){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() + (2 * 16);

            if(counter < 2 && time > 0.3){
                x = owner->getSpriteRecX()+ (counter * 16) ;

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                counter ++;
                time = 0;
                deltaTime = clock.restart().asSeconds();
            }
            else if(counter == 2){
                counter = 0;
            }
        }
        //moving left
        else if(owner->getMovingDirection()==LEFT){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY();

            if(counter < 4 && time > 0.3){
                x = owner->getSpriteRecX()+ (counter * 16) ;

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                counter ++;
                time = 0;
                deltaTime = clock.restart().asSeconds();
            }
            else if(counter == 4){
                counter = 0;
            }
        }
        //moving right
        else if(owner->getMovingDirection()==RIGHT){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() + 16;

            if(counter < 4 && time > 0.3){
                x = owner->getSpriteRecX()+ (counter * 16) ;

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                counter ++;
                time = 0;
                deltaTime = clock.restart().asSeconds();
            }
            else if(counter == 4){
                counter = 0;
            }
        }
    }
    //spring animation
    else if(owner->getID() == SPRING){
        //if dead play dead animation
        if(owner->getHP() <= 0){
            if(!killed){
                killed = true;
                counter = 0;
                owner->disableComponent("EnemyComp");
            }
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            y = owner->getSpriteRecY() + 16;

            if(counter < 4 && time > 0.3){
                x = owner->getSpriteRecX()+ (counter * 16 );

                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                time = 0;
                counter++;
                deltaTime = clock.restart().asSeconds();
                
            }
            else if(counter >= 4)
            {
                owner->toggleVisibility();
                setEnabled(false);
                owner->setReturnToPool(true);
                killed = false;
                counter = 0;
            }
        }
        //if not dead

        //if on floor play compress animation
        else if(owner->collisions.floor || counter > 0){
            float deltaTime = clock.restart().asSeconds();
            time += deltaTime;
            counter++;
            y = owner->getSpriteRecY();
            x = owner->getSpriteRecX() + 16;
            owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));

            if(time > 0.1){
                x = owner->getSpriteRecX();
                owner->getSprite()->setTextureRect(IntRect({x,y},{w,h}));
                time = 0;
                counter = 0;
                deltaTime = clock.restart().asSeconds();
            }
        }
    }
}