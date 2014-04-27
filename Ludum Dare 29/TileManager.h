#pragma once



#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "forwards.h"
#include "ResourceManager.h"

class TileManager{
public:
	enum EFFECTSTATE{
		none,
		shaking,
		spinning,
		zooming,
		spinzoom,
	};
	TileManager(ResourceManager<sf::Texture,std::string>* resourceManager);
	void updateAll(double frameTime);
	void renderAll(sf::RenderTarget* renderTarget);
	EntityPtrList& getRelevantEntities(Entity::SURFACE_LEVEL surfaceLevel);
	void scheduleEntityAdd(Entity* entity, Entity::SURFACE_LEVEL surfaceLevel);
	void changeLevel();
	void scheduleEntityLevelChange(Entity* entity);
	Entity* getPlayer(Entity::SURFACE_LEVEL);
	void changeEffect(EFFECTSTATE state);
private:
	bool zincreasing;
	float zoomamount;
	float rotatedeg;
	bool first;
	sf::View defaultview;
	sf::View view;
	EFFECTSTATE state_;
	std::unique_ptr<sf::Sprite> grassbg;
	std::unique_ptr<sf::Sprite> stonebg;
	ResourceManager<sf::Texture, std::string>* resourceManager_;

	void add(Entity* entity, Entity::SURFACE_LEVEL surfaceLevel);
	void changeEntityLevel(Entity* entity);
	std::vector<std::pair<Entity*, Entity::SURFACE_LEVEL>> entitiesToAdd_;
	std::vector<Entity*> entitiesToChange_;
	Entity::SURFACE_LEVEL currentSurface_;
	std::vector<std::unique_ptr<Entity>> aboveGround_;
	std::vector<std::unique_ptr<Entity>> belowGround_;
};