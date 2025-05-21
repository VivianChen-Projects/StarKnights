#include "GD_Trn.h"

void GD_Trn::moveUp(GD_2DBlockObject* obj){
    obj->move(0,-1);
}

void GD_Trn::moveDown(GD_2DBlockObject* obj){
    obj->move(0,1);
}

void GD_Trn::moveLeft(GD_2DBlockObject* obj){
    obj->move(-1,0);
}

void GD_Trn::moveRight(GD_2DBlockObject* obj){
    obj->move(1,0);
}


