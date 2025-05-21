#include "orbitComp.hpp"

//makes an obj orbit around the given point 
void OrbitComp::perform()
{
    GD_ModularObject* owner = getOwner();

    if(Direction = direction::right)
        angle += speed;
    else if(Direction = direction::left)
        angle -= speed;

    if(angle >= 360)
        angle -= 360;
    else if(angle <= 0)
        angle += 360;

    float rads = angle * (M_PI/180.f);
    float newx = centerX + radius * cos(rads) - owner->getWidth() / 2;
    float newy = centerY + radius * sin(rads) - owner->getHeight() / 2;

    owner->getSprite()->setPosition({newx, newy});
}