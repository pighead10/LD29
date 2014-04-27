#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TileManager.h"
#include "Hole.h"

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
	type_ = ENTITY_PLAYER;
	haswep = false;
	state = walking;
	spintimer = 0;
	testshader.loadFromFile("media/shaders/swirl.frag",sf::Shader::Vertex);
	changetimer = 0;
}

void Player::render(sf::RenderTarget* target){
	target->draw(*sprite_.get(),&testshader);
	if (haswep){
		weapon_->render(target);
	}
}

void Player::changeWeapon(Weapon* weapon){
	haswep = true;
	weapon_ = std::unique_ptr<Weapon>(weapon);
}

void Player::update(double frameTime){
	using namespace sf;

	layerTimer_ += frameTime;
	if (state == spinning){
		if (sprite_->getOrigin().x == 0){
			sprite_->setOrigin(sprite_->getLocalBounds().width / 2, sprite_->getLocalBounds().height / 2);
			sprite_->move(sprite_->getLocalBounds().width / 2, sprite_->getLocalBounds().height / 2);
		}
		
		sprite_->rotate(5);
		spintimer += frameTime;
		if (spintimer >= 200){
			spintimer = 0;
			state = walking;
			sprite_->setRotation(0);
			sprite_->setOrigin(0, 0);
			
		}
	}
	else if (state == walking){
		sfld::Vector2f direction;
		if (Keyboard::isKeyPressed(Keyboard::A)){
			direction.x = -1;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)){
			direction.y = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)){
			direction.x = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::W)){
			direction.y = -1;
		}
		gotoTile(sfld::Vector2i(tilePosition_.x + direction.x, tilePosition_.y + direction.y));
		move(frameTime);
	}

	

	if (Keyboard::isKeyPressed(Keyboard::Space)){
		if (layerTimer_ > 2000){
			if (level_ == ABOVE_GROUND){
				parent_->scheduleEntityAdd(new Hole(resourceManager_, getTilePosition(), parent_),level_);
			}
			if (state != waiting){
				state = waiting;
				sprite_->setTexture(resourceManager_->get("playershovel"));
				
			}
			if (layerTimer_ == 3000){
				parent_->changeEffect(TileManager::spinzoom);
			}
			if (layerTimer_ > 4000){
				state = walking;
				sprite_->setTexture(resourceManager_->get("player"));
				scheduleLevelChange();
				layerTimer_ = 0;
				
			}
		}
	}

	
	
	std::vector<Entity*> collisions = getCollisions();
	if (collisions.size() > 0){
		collided = true;
		sprite_->setTexture(resourceManager_->get("testcollided"));
	}
	if (collided){
		ctimer += frameTime;
		if (ctimer > 500){
			sprite_->setTexture(resourceManager_->get("player"));
			ctimer = 0;
			collided = false;
		}
	}
	if (haswep){
		weapon_->update(frameTime);
	}
}