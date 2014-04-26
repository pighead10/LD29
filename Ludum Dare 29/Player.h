#pragma once

#include "Entity.h"
#include "ResourceManager.h"

class Player : public Entity{
public:
	explicit Player(TileManager* tileManager,sf::Sprite* sprite,ResourceManager<sf::Texture,std::string>* resourceManager);
	void update(double frameTime);
private:
	double layerTimer_;
	bool collided;
	double ctimer;
	ResourceManager<sf::Texture, std::string>* resourceManager_;
};