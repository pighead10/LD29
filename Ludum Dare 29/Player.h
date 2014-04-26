#pragma once

#include "Entity.h"

class Player : public Entity{
public:
	explicit Player(TileManager* tileManager,sf::Sprite* sprite);
	void update(double frameTime);
};