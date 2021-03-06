#pragma once

#include "Entity.h"
#include "ResourceManager.h"

#include "Weapon.h"

class Weapon;

class Player : public Entity{
public:
	
	Player(TileManager* tileManager,sf::Sprite* sprite,ResourceManager<sf::Texture,std::string>* resourceManager);
	void update(double frameTime);
	void changeWeapon(Weapon* weapon);
	void render(sf::RenderTarget* target);
private:
	int changetimer;
	sf::Shader testshader;
	int spintimer;
	bool haswep;
	std::unique_ptr<Weapon> weapon_;
	double layerTimer_;
	bool collided;
	double ctimer;
	ResourceManager<sf::Texture, std::string>* resourceManager_;
};