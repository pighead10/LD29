#pragma once



#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "forwards.h"

class TileManager{
public:
	void updateAll(double frameTime);
	void renderAll(sf::RenderTarget* renderTarget);
	EntityPtrList& getRelevantEntities(Entity::SURFACE_LEVEL surfaceLevel);
	void add(Entity* entity, Entity::SURFACE_LEVEL surfaceLevel);
private:
	Entity::SURFACE_LEVEL currentSurface_;
	std::vector<std::unique_ptr<Entity>> aboveGround_;
	std::vector<std::unique_ptr<Entity>> belowGround_;
};