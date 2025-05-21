#pragma once

#include "GD_ModularObject.h"
#include "GD_Component.h"

#include "physicsComp.hpp"
#include "ladderComp.h"
#include "playerMoveComp.hpp"
#include "enemyComp.h"
#include "EnemyDamageComp.hpp"
#include "spriteComp.h"
#include "hammerComp.h"

#include "Definitions.hpp"

//makes all the objs and inits them 
class ObjectFactory{
	public:
	    static GD_ModularObject* makePlayer(int x,int y);
	    static GD_ModularObject* makeEnemy(string state, int x,int y);
        static GD_ModularObject* makePeach(int x,int y);
        static GD_ModularObject* makePlatform(int x,int y);
        static GD_ModularObject* makeLadder(int x,int y);
        static GD_ModularObject* makeSpawner(string direction, int x,int y);
        static GD_ModularObject* makeSpawnerRope(int x,int y);
        static GD_ModularObject* makeFireBall(string moveDirection, int x,int y);
        static GD_ModularObject* makeSpring(string moveDirection, int x,int y);
        static GD_ModularObject* makeBarrel(string moveDirection, int x,int y);
        static GD_ModularObject* makeHammer(GD_ModularObject* player);
        
};
