#include "GD_ModularObject.h"

GD_ModularObject::GD_ModularObject(std::string objName, 
    std::string textureName, int xV, int yV):
    GD_2DBlockObject(objName,textureName, xV, yV){
        IsVisible = true;

        collisions.jumping= false;
        collisions.climbing = false;
        collisions.startClimbBot = false;
        collisions.startClimbTop = false;

        hp = 1;
}

GD_ModularObject::GD_ModularObject(std::string objName, 
        std::string textureName):
        GD_2DBlockObject(objName,textureName){
            IsVisible = true;

            collisions.jumping= false;
            collisions.climbing = false;
            collisions.startClimbBot = false;
            collisions.startClimbTop = false;

            hp = 1;
}


GD_ModularObject::~GD_ModularObject(){
    for(GD_Component* cmp: componentList)
        delete cmp;
}

void GD_ModularObject::attachComponent(GD_Component* component){
    componentList.push_back(component);
    component->attachOwner(this);
}

GD_Component* GD_ModularObject::getComponent(std::string componentName){
    for(GD_Component* cmp: componentList)
        if(cmp->getName() == componentName)
            return cmp;
    return nullptr;
}

void GD_ModularObject::update(){
    for(GD_2DBlockObject* child: getAllChildren())
        child->update();
    for(GD_Component* cmp: componentList)
        cmp->perform();
}

bool GD_ModularObject::isVisible()
{
    return IsVisible;
}

void GD_ModularObject::toggleVisibility()
{
    IsVisible = !IsVisible;
}

void GD_ModularObject::disableComponent(string compName)
{
    if(componentList.size() <= 0)
        return;

    for(int i = 0; i < componentList.size(); i++)
        if(componentList.at(i)->getName() == compName)
        {
            componentList.at(i)->setEnabled(false);
            break;
        }
}

void GD_ModularObject::enableComponent(string compName)
{
    if(componentList.size() <= 0)
        return;
        
    for(int i = 0; i < componentList.size(); i++)
        if(componentList.at(i)->getName() == compName)
        {
            componentList.at(i)->setEnabled(true);
            break;
        }
}

vector<GD_Component*> GD_ModularObject::getComponentList()
{
    return componentList;
}

void GD_ModularObject::enableAllComps()
{
    for(int i = 0; i < componentList.size(); i++)
        componentList.at(i)->setEnabled(true);
}

void GD_ModularObject::disableAllComps()
{
    for(int i = 0; i < componentList.size(); i++)
        componentList.at(i)->setEnabled(false);
}

void GD_ModularObject::setHP(int newHP)
{
    hp = newHP;
}

int GD_ModularObject::getHP()
{
    return hp;
}

void GD_ModularObject::setHeight(int newHieght)
{
    height = newHieght;
}

void GD_ModularObject::setWidth(int newWidth)
{
    width = newWidth;
}

void GD_ModularObject::setDead(bool IsDead)
{
    isDead = IsDead;
}

bool GD_ModularObject::getDeathStatus()
{
    return isDead;
}

void GD_ModularObject::setReturnToPool(bool Bool)
{
    returnToPool = Bool;
}

bool GD_ModularObject::getReturnToPool()
{
    return returnToPool;
}