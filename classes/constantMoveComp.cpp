#include "constantMoveComp.hpp"

//moves in a constant direction, cant change
void ConstantMoveComp::perform()
{
    if(!getEnabled())
        return;

    GD_ModularObject* owner = getOwner();

    if(direction == Direction::up)
        owner->move(0, speed);
    else if(direction == Direction::down)
        owner->move(0, -speed);
    else if(direction == Direction::right)
        owner->move(speed, 0);
    else if(direction == Direction::left)
        owner->move(-speed, 0);
}