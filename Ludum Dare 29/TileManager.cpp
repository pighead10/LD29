#include "stdafx.h"
#include "TileManager.h"
#include "Entity.h"
#include "ResourceManager.h"

TileManager::TileManager(ResourceManager<sf::Texture, std::string>* resourceManager) 
: currentSurface_(Entity::ABOVE_GROUND),resourceManager_(resourceManager){
	grassbg = std::unique_ptr<sf::Sprite>(new sf::Sprite(resourceManager_->get("grassbg")));
	stonebg = std::unique_ptr<sf::Sprite>(new sf::Sprite(resourceManager_->get("stonebg")));
}

void TileManager::scheduleEntityLevelChange(Entity* entity){
	entitiesToChange_.push_back(entity);
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

void TileManager::scheduleEntityAdd(Entity* entity, Entity::SURFACE_LEVEL surfaceLevel){
	entitiesToAdd_.push_back(std::make_pair(entity, surfaceLevel));
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
	for (auto& it : entitiesToChange_){
		changeEntityLevel(it);
		it->levelChange();
		if (it->getType() == Entity::ENTITY_PLAYER){
			changeLevel();
		}
	}
	entitiesToChange_.clear();

	for (auto& it : entitiesToAdd_){
		add(it.first, it.second);
	}
	entitiesToAdd_.clear();
}

void TileManager::renderAll(sf::RenderTarget* renderTarget){
	if (currentSurface_ == Entity::ABOVE_GROUND){
		renderTarget->draw(*grassbg.get());
		for (auto& it : aboveGround_){
			it->render(renderTarget);
		}
	}
	else if (currentSurface_ == Entity::BELOW_GROUND){
		renderTarget->draw(*stonebg.get());
		for (auto& it : belowGround_){
			it->render(renderTarget);
		}
	}
}

Entity* TileManager::getPlayer(Entity::SURFACE_LEVEL surfaceLevel){
	EntityPtrList& list = (surfaceLevel == Entity::ABOVE_GROUND ? aboveGround_ : belowGround_);
	for (auto& it : list){
		if (it->getType() == Entity::ENTITY_PLAYER){
			return it.get();
		}
	}
	return NULL;
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