#include "GD_2DBlockObject.h"

//constructor for object with sprite sheet
GD_2DBlockObject::GD_2DBlockObject(std::string objName, std::string textureName, int xV, int yV):
        GD_GameObject(objName){

    if(texture.loadFromFile(textureName))
        sprite = new sf::Sprite(texture);
    
    //the initial position of the texture
    spriteRecX = xV;
    spriteRecY = yV; 
    
    // size of the sprite sheet
    frameH = static_cast<int>(texture.getSize().y);
    frameW = static_cast<int>(texture.getSize().x);
    
    visible = true;

    ID = objName;
}

//constructor for item with no sprite sheet
GD_2DBlockObject::GD_2DBlockObject(std::string objName, std::string textureName):
        GD_GameObject(objName){
    if(texture.loadFromFile(textureName))
        sprite = new sf::Sprite(texture);
    sprite->setTextureRect(sf::IntRect({0,0}, {static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y)}));

    sprite->setScale({TILESCALE/8, TILESCALE/8});
    sprite->move({TILESCALE/2, TILESCALE/2});
    
    height = static_cast<int>(texture.getSize().y) * (TILESCALE/8);
    width = static_cast<int>(texture.getSize().x) * (TILESCALE/8);
    visible = true;

    ID = objName;
}

void GD_2DBlockObject::setSprite(){

    //frameX and frameY is the amount of row and column
    sprite->setTextureRect(sf::IntRect({spriteRecX,spriteRecY}, {frameW/frameX, frameH/frameY}));
    sprite->setScale({TILESCALE/8, TILESCALE/8});
    sprite->move({TILESCALE/2, TILESCALE/2});

    //height and width for one sprite in the sprite sheet
    height = (static_cast<int>(texture.getSize().y)/frameY)* (TILESCALE/8);
    width = (static_cast<int>(texture.getSize().x)/frameX)* (TILESCALE/8);
}

GD_2DBlockObject::~GD_2DBlockObject(){
    delete sprite;
}

void GD_2DBlockObject::init(){}

void GD_2DBlockObject::draw(sf::RenderWindow *window){
    window->draw(*sprite);
}

void GD_2DBlockObject::setParent(GD_2DBlockObject* parentVal){
    parent = parentVal;
    //return &this;
}
        
void GD_2DBlockObject::attachChild(GD_2DBlockObject* child){
    children.push_back(child);
    child->setParent(this);    
}

std::vector<GD_2DBlockObject*> GD_2DBlockObject::getAllChildren(){
    return children;
}

bool GD_2DBlockObject::isVisible(){ return visible; }
void GD_2DBlockObject::toggleVisibility(){ visible = !visible; }
sf::Sprite* GD_2DBlockObject::getSprite(){ return sprite; }

GD_2DBlockObject* GD_2DBlockObject::getParent(){
    return parent;
}

GD_2DBlockObject* GD_2DBlockObject::getChild(std::string objName){
    for(GD_2DBlockObject* child: children)
        if(child->getName() == objName)
            return child;
    return nullptr;
}

void GD_2DBlockObject::setTileXY(int xV, int yV){
    sprite->setPosition({TILESCALE*(xV+0.f), TILESCALE*(yV+0.f)});
}

int GD_2DBlockObject::getHeight()
{
    return height;
}

int GD_2DBlockObject::getWidth()
{
    return width;
}

void GD_2DBlockObject::move(int xPixels, int yPixels)
{
    sprite->move({xPixels+.0f, -yPixels+.0f});
}

void GD_2DBlockObject::scaleObject(float scale)
{
    sprite->scale({scale, scale});
    height *= scale;
    width *= scale;
}

string GD_2DBlockObject::getID(){
    return ID;
}

void GD_2DBlockObject::setMovingDirection(string direction){
    movingDirection = direction;
}

string GD_2DBlockObject::getMovingDirection(){
    return movingDirection;
}

void GD_2DBlockObject::setFaceDirection(string direction){
    faceDirection = direction;
}

string GD_2DBlockObject::getFaceDirection(){
    return faceDirection;
}

void GD_2DBlockObject::setState(string enemyState){
    state = enemyState;
}

string GD_2DBlockObject::getState(){
    return state;
}

void GD_2DBlockObject::setSpriteRecXY(int xV, int yV){
    spriteRecX = xV;
    spriteRecY = yV;
}

int GD_2DBlockObject::getSpriteRecX(){
    return spriteRecX;
}

int GD_2DBlockObject::getSpriteRecY(){
    return spriteRecY;
}

void GD_2DBlockObject::setFrameXY(int xV, int yV){
    frameX = xV;
    frameY = yV;
}

int GD_2DBlockObject::getFrameX(){
    return frameX;
}

int GD_2DBlockObject::getFrameY(){
    return frameY;
}

int GD_2DBlockObject::getFrameH(){
    return frameH;
}

int GD_2DBlockObject::getFrameW(){
    return frameW;
}