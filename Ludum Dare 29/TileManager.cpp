#include "stdafx.h"
#include "TileManager.h"
#include "Entity.h"
#include "ResourceManager.h"

TileManager::TileManager(ResourceManager<sf::Texture, std::string>* resourceManager) 
: currentSurface_(Entity::ABOVE_GROUND),resourceManager_(resourceManager){
	grassbg = std::unique_ptr<sf::Sprite>(new sf::Sprite(resourceManager_->get("grassbg")));
	stonebg = std::unique_ptr<sf::Sprite>(new sf::Sprite(resourceManager_->get("stonebg")));
	
	first = true;
	state_ = spinzoom;
	rotatedeg = 0;
	zoomamount = 0;
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

void TileManager::changeEffect(EFFECTSTATE state){
	state_ = state;
	if (state_ == none){
		view = defaultview;
	}
	else if (state_ == spinning){
		rotatedeg = 0;
	}
	else if (state_ == zooming){
		zoomamount = 1;
		zincreasing = false;
	}
	else if (state_ == spinzoom){
		rotatedeg = 0;
		zoomamount = 0;
		zincreasing = true;
	}
}

void TileManager::add(Entity* entity, Entity::SURFACE_LEVEL surfaceLevel){
	EntityPtrList& list = (surfaceLevel == Entity::ABOVE_GROUND ? aboveGround_ : belowGround_);
	list.push_back(std::unique_ptr<Entity>(entity));
}

void TileManager::updateAll(double frameTime){
	if (shaking)
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
	if (first){
		defaultview = renderTarget->getDefaultView();
		view = defaultview;
		first = false;
	}
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
	if (state_ == shaking){
		float xr = rand() % 10 - 5;
		float yr = rand() % 10 - 5;
		view.move(xr, yr);
	}
	else if (state_ == spinning){
		rotatedeg += 0.1;
		view.setRotation(rotatedeg);
	}
	else if (state_ == zooming){
		float amount = 0.0005;
		float n1 = (zincreasing ? 1+amount : 1-amount);
		float n = (zincreasing ? amount : -amount);
		zoomamount += n;
		if (zoomamount >= 2 || zoomamount <= -0.5){
			zincreasing = !zincreasing;
		}
		view.zoom(n1);
	}
	else if (state_ == spinzoom){
		float amount = 0.0005;
		if (zoomamount > 1){
			zincreasing = false;
			
		}
		if (zincreasing){
			zoomamount += amount;
			view.zoom(1 - amount);
		}
		else{
			zoomamount -= amount;
			view.zoom(1 + amount);
		}
		if (zoomamount < 0){
			changeEffect(none);
		}
		
		rotatedeg += 0.09;
		view.setRotation(rotatedeg);
	}
	else if (state_ == none){
		view = defaultview;
	}
	renderTarget->setView(view);
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