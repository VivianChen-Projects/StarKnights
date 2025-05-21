#pragma once

#include "GD_GameObject.h"
#include "Definitions.hpp"

using namespace std;
using namespace sf;

//mostly added stuff for sprite animations
class GD_2DBlockObject: public GD_GameObject{
	private:
		GD_2DBlockObject* parent;
		vector<GD_2DBlockObject*> children;
		Sprite* sprite; 
        Texture texture;
		bool visible;
        string ID;
        string movingDirection;
        int frameX, frameY;
        int spriteRecX, spriteRecY;
        int frameW, frameH;
        string state;
        string faceDirection;

    protected:
        int height, width;

	public:
        GD_2DBlockObject(std::string objName, std::string textureName, int xV, int yV);
	    GD_2DBlockObject(std::string objName, std::string textureName);
	    ~GD_2DBlockObject();
	    
	    void setParent(GD_2DBlockObject* parentVal);
        void attachChild(GD_2DBlockObject* child);

        void setSprite();

        GD_2DBlockObject* getParent();
        GD_2DBlockObject* getChild(std::string objName);
        std::vector<GD_2DBlockObject*> getAllChildren();
        
        bool isVisible();
        void toggleVisibility();
        sf::Sprite* getSprite();
        void move(int xPixels, int yPixels);
        
        void setTileXY(int xV, int yV);
        int getHeight();
        int getWidth();
        
        void init() override;
        void draw(sf::RenderWindow *window) override;

        void scaleObject(float scale);

        string getID();

        void setMovingDirection(string direction);
        string getMovingDirection();

        void setFaceDirection(string direction);
        string getFaceDirection();

        void setState(string enemyState);
        string getState();

        void setSpriteRecXY(int xV, int yV);
        int getSpriteRecX();
        int getSpriteRecY();

        void setFrameXY(int xV, int yV);
        int getFrameX();
        int getFrameY();
        int getFrameW();
        int getFrameH();
};
