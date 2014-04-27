#pragma once

#include "Weapon.h"
#include "ResourceManager.h"

class UpwardsStabWeapon : public Weapon{
public:
	UpwardsStabWeapon(ResourceManager<sf::Texture, std::string>* resourceManager, Entity* parent);
	void update(double frameTime);
	void render(sf::RenderTarget* renderTarget);
	Weapon* create(Entity* paren);
private:
	bool torender;
	double rendTimer;
	double rtimer_;
	ResourceManager<sf::Texture, std::string>* resourceManager_;
};