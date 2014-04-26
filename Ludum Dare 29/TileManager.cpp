#include "stdafx.h"
#include "TileManager.h"
#include "Entity.h"

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
	if (currentSurface_ == Entity::ABOVE_GROUND){
		return aboveGround_;
	}
	else if (currentSurface_ == Entity::BELOW_GROUND){
		return belowGround_;
	}
	assert("currentSurface is not a proper value!");
	return EntityPtrList();
}