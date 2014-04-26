#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TileManager.h"

Player::Player(TileManager* tileManager,sf::Sprite* sprite,ResourceManager<sf::Texture,std::string>* resourceManager):resourceManager_(resourceManager){
	toremove_ = false;
	parent_ = tileManager;
	level_ = ABOVE_GROUND;
	speed_ = 0.5f;
	sprite_ = std::unique_ptr<sf::Sprite>(sprite);
	ctimer = 0;
	collided = false;
	radius_ = 16;
	layerTimer_ = 0;
}

void Player::update(double frameTime){
	using namespace sf;

	layerTimer_ += frameTime;

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

	if (Keyboard::isKeyPressed(Keyboard::Space)){
		if (layerTimer_ > 2000){
			changeLevel();
			parent_->changeLevel();
			layerTimer_ = 0;
		}
	}

	gotoTile(sfld::Vector2i(tilePosition_.x + direction.x,tilePosition_.y+direction.y));
	move(frameTime);
	std::vector<Entity*> collisions = getCollisions();
	if (collisions.size() > 0){
		collided = true;
		sprite_->setTexture(resourceManager_->get("testcollided"));
	}
	if (collided){
		ctimer += frameTime;
		if (ctimer > 500){
			sprite_->setTexture(resourceManager_->get("test"));
			ctimer = 0;
			collided = false;
		}
	}
}