#pragma once

#define TILESCALE 24 //final

//MUST CHANGE ACCORDINGLY
#define NUMBEROFSTAGES 3
extern int SoundVolume, MusicVolume; //0 - 100

#define FRAMERATE 60

#define PIXEL TILESCALE * 0.16

#define PLAYERMOVEMENTSPEED TILESCALE * 0.1
#define PLAYERJUMPHEIGHT TILESCALE * 2
#define PLAYERINVULTIME 150
#define HAMMERPOWERUPDURATION 600

#define GRAVITY -TILESCALE * 0.15
#define GROUNDCLIPAMOUNT TILESCALE * 0.167
#define COLLISIONLEEWAY TILESCALE * 0.2

//for scene returns
#define ONGOING -1
#define LOST 2
#define WIN 37

//main menu returns
//#define ONGOING -1
#define STARTGAME 2
#define SETTINGS 3
#define EXITGAME 4

//death screen returns
#define RESTART 5
#define MAINMENU 4

//object names serves as IDs, keeps names consistant
#define PLAYER "player"
#define ENEMY "enemy"
#define PLATFORM "platform"
#define LADDER "ladder"
#define SPAWNER "spawner"
#define ROPE "rope"
#define FIREBALL "fire ball"
#define FIREBALLMOVEMENTSPEED 2
#define SPRING "spring"
#define SPRINGJUMPHEIGHT TILESCALE * 3
#define SPRINGMOVEMENTSPEED 3
#define BARREL "barrel"
#define PEACH "peach"
#define HAMMER "hammer"
#define HAMMERITEM "hammeritem"

//Directions for enemy
#define LEFT "left"
#define RIGHT "right"
#define UP "up"
#define DOWN "down"
#define STATIONARY "stationary"

//States for Mario
#define WALK_L "walkLeft"
#define WALK_R "walkRight"
#define CLIMBING "climbing"
#define DEFAULT_L "defaultLeft"
#define DEFAULT_R "defaultRight"
#define NONE "none"

//States for DK
#define IDLE "idle"
#define THROW_BARREL_D "throwBarrelDown"
#define THROW_BARREL_L "throwBarrelLeft"
#define THROW_BARREL_R "throwBarrelRight"

//names for sounds
#define BGM "bgm"
#define JUMPSFX "jumpsfx"
#define WALKINGSFX "walkingsfx"
#define ENEMYDEATH "enemydeath"
#define HAMMERBGM "hammerbgm"

//bb10 stuff
#define BASESPAWNRATE 10 * 60