#include "stdafx.h"
#include "Player.h"

Player::Player(TileManager* tileManager,sf::Sprite* sprite){
	toremove_ = false;
	parent_ = tileManager;
	level_ = ABOVE_GROUND;
	speed_ = 1.f;
}

void Player::update(double frameTime){
	using namespace sf;
	sfld::Vector2f direction;
	if (Keyboard::isKeyPressed(Keyboard::A)){
		direction.x = -1;
		direction.y = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)){
		direction.x = 0;
		direction.y = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)){
		direction.x = 1;
		direction.y = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::W)){
		direction.x = 0;
		direction.y = -1;
	}

	gotoTile(sfld::Vector2i(tilePosition_.x + direction.x,tilePosition_.y+direction.y));
	move(frameTime);
}