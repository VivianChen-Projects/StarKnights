#pragma once

#include "GD_AtlasParserM.h"
#include <SFML/Graphics.hpp>

//removed the atlas functionality

class GD_GameResource{
	public:
		static GD_GameResource* createInstance();
		sf::Texture* getTexture();
		sf::Font* getFont();
	private:
		static GD_GameResource* myInstance;
		sf::Texture texture;
		sf::Font font;
		GD_GameResource();
};
