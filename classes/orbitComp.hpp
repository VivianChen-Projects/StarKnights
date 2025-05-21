#pragma once

#include "GD_Component.h"
#include "Definitions.hpp"
#include "iostream"
#include "math.h"

using namespace std;

//makes an obj orbit around the given point 

class OrbitComp: public GD_Component
{
    public:
    enum direction{left, right};
        OrbitComp(GD_ModularObject* owner, int centerx, int centery, int Radius, float startAngle, float Speed, direction direction):GD_Component("OrbitComp")
        {
            attachOwner(owner);
            centerX = centerx;
            centerY = centery;
            radius = Radius;
            angle = startAngle;
            speed = Speed;
            Direction = direction;
        }

        void perform() override;

    private:
        int centerX, centerY, radius;
        float angle, speed;
        direction Direction;
};