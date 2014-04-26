#include "stdafx.h"
#include "TileManager.h"
#include "Entity.h"

TileManager::TileManager() : currentSurface_(Entity::ABOVE_GROUND){

}

void TileManager::changeEntityLevel(Entity* entity){
	Entity::SURFACE_LEVEL entSurface = entity->getSurfaceLevel();
	EntityPtrList& list = (entSurface == Entity::ABOVE_GROUND ? aboveGround_ : belowGround_);
	EntityPtrList& other = (entSurface == Entity::ABOVE_GROUND ? belowGround_ : aboveGround_);
	for (auto& it = list.begin(); it != list.end(); it++){
		if (it->get() == entity){
			Entity* e = it->release();
			other.push_back(std::unique_ptr<Entity>(e));
			list.erase(it);
			break;
		}
	}
}

void TileManager::changeLevel(){
	currentSurface_ = (currentSurface_ == Entity::ABOVE_GROUND ? Entity::BELOW_GROUND : Entity::ABOVE_GROUND);
}

void TileManager::add(Entity* entity, Entity::SURFACE_LEVEL surfaceLevel){
	EntityPtrList& list = (surfaceLevel == Entity::ABOVE_GROUND ? aboveGround_ : belowGround_);
	list.push_back(std::unique_ptr<Entity>(entity));
}

void TileManager::updateAll(double frameTime){
	for (auto& it = aboveGround_.begin(); it != aboveGround_.end();){
		if ((*it)->isDestroyed()){
			it = aboveGround_.erase(it);
		}
		else{
			(*it)->update(frameTime);
			it++;
		}
	}
	for (auto& it = belowGround_.begin(); it != belowGround_.end();){
		if ((*it)->isDestroyed()){
			it = belowGround_.erase(it);
		}
		else{
			(*it)->update(frameTime);
			it++;
		}
	}
}

void TileManager::renderAll(sf::RenderTarget* renderTarget){
	if (currentSurface_ == Entity::ABOVE_GROUND){
		for (auto& it : aboveGround_){
			it->render(renderTarget);
		}
	}
	else if (currentSurface_ == Entity::BELOW_GROUND){
		for (auto& it : belowGround_){
			it->render(renderTarget);
		}
	}
}

EntityPtrList& TileManager::getRelevantEntities(Entity::SURFACE_LEVEL surfaceLevel){
	if (surfaceLevel == Entity::ABOVE_GROUND){
		return aboveGround_;
	}
	else if (surfaceLevel == Entity::BELOW_GROUND){
		return belowGround_;
	}
	assert("currentSurface is not a proper value!");
	return EntityPtrList();
}