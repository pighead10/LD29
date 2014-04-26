#include "stdafx.h"
#include "Entity.h"
#include "TileManager.h"

void Entity::update(double frameTime){

}

sfld::Vector2f Entity::getCentre() const{
	return sprite_->getPosition() + sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2);
}

void Entity::render(sf::RenderTarget* renderTarget){
	renderTarget->draw(*sprite_.get());
}

void Entity::gotoTile(const sfld::Vector2i& tilePosition){
	targetTile_ = tilePosition;
}

bool Entity::isDestroyed() const{
	return toremove_;
}

void Entity::setTilePosition(const sfld::Vector2i& tilePosition){
	tilePosition_ = tilePosition;
}

sfld::Vector2f Entity::getRealPosition() const{
	return sprite_->getPosition();
}

void Entity::setRealPosition(const sfld::Vector2f position){
	sprite_->setPosition(position);
}

std::vector<Entity*> Entity::getCollisions(){
	EntityPtrList& entities = parent_->getRelevantEntities(level_);
	std::vector<Entity*> collisions;
	for (auto& it : entities){
		if (sfld::Vector2f(it->getRealPosition() - getRealPosition()).length() <= it->radius_){
			collisions.push_back(it.get());
		}
	}
	return collisions;
}

void Entity::move(double frameTime){
	sfld::Vector2f targetPos = sfld::Vector2f(targetTile_.x * TILE_SIZE, targetTile_.y*TILE_SIZE);
	if (getRealPosition() != targetPos){
		float distanceToMove = speed_*frameTime;
		if (sfld::Vector2f(getRealPosition() - targetPos).length() < distanceToMove){
			setRealPosition(targetPos);
		}
		else{
			sfld::Vector2f direction = sfld::Vector2f(targetPos - getRealPosition()).normalise();
			setRealPosition(getRealPosition() + direction*distanceToMove);
		}
		if (sfld::Vector2f(getRealPosition() - targetPos).length() < (TILE_SIZE / 2)){
			setTilePosition(targetTile_);
		}
	}
}