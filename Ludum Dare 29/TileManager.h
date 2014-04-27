#pragma once



#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "forwards.h"

class TileManager{
public:
	TileManager();
	void updateAll(double frameTime);
	void renderAll(sf::RenderTarget* renderTarget);
	EntityPtrList& getRelevantEntities(Entity::SURFACE_LEVEL surfaceLevel);
	void scheduleEntityAdd(Entity* entity, Entity::SURFACE_LEVEL surfaceLevel);
	void changeLevel();
	void scheduleEntityLevelChange(Entity* entity);
	Entity* getPlayer(Entity::SURFACE_LEVEL);
private:
	void add(Entity* entity, Entity::SURFACE_LEVEL surfaceLevel);
	void changeEntityLevel(Entity* entity);
	std::vector<std::pair<Entity*, Entity::SURFACE_LEVEL>> entitiesToAdd_;
	std::vector<Entity*> entitiesToChange_;
	Entity::SURFACE_LEVEL currentSurface_;
	std::vector<std::unique_ptr<Entity>> aboveGround_;
	std::vector<std::unique_ptr<Entity>> belowGround_;
};