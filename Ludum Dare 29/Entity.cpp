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

void Entity::setPositionFromTile(sfld::Vector2i tilePos){
	setTilePosition(tilePos);
	setRealPosition(sfld::Vector2f(tilePos.x*TILE_SIZE, tilePos.y*TILE_SIZE));
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

void Entity::changeLevel(){
	parent_->changeEntityLevel(this);
	level_ = (level_ == ABOVE_GROUND ? BELOW_GROUND : ABOVE_GROUND);
}

Entity::SURFACE_LEVEL Entity::getSurfaceLevel() const{
	return level_;
}

std::vector<Entity*> Entity::getCollisions(){
	EntityPtrList& entities = parent_->getRelevantEntities(level_);
	std::vector<Entity*> collisions;
	for (auto& it : entities){
		if (it.get() != this){
			if (sfld::Vector2f(it->getCentre() - getCentre()).length() <= it->radius_*2-5){
				collisions.push_back(it.get());
			}
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