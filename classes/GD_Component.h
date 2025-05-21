#pragma once

class GD_ModularObject;

#include "GD_GameObject.h"
#include "GD_ModularObject.h"

class GD_Component{
     private:
        std::string name;
        GD_ModularObject* owner;
        bool enabled;
    public:
        GD_Component(std::string name);
        void attachOwner(GD_ModularObject* owner);
        GD_ModularObject* getOwner();
        std::string getName();
        bool getEnabled();
        void setEnabled(bool val);
        virtual void perform() = 0;
};
