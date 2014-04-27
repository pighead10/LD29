#pragma once

#include "Vector.h"
#include "forwards.h"

#define TILE_SIZE 32

class TileManager;
class Weapon;

class Entity{
public:
	enum SURFACE_LEVEL{
		ABOVE_GROUND,
		BELOW_GROUND
	};

	enum ENTITY_TYPE{
		ENTITY_PLAYER,
		ENTITY_OTHER,
		ENTITY_HOLE,
		ENTITY_SPRING
	};

	virtual void update(double frameTime);
	virtual void render(sf::RenderTarget* renderTarget);
	virtual void gotoTile(const sfld::Vector2i& tilePosition);
	virtual void move(double frameTime);
	sfld::Vector2f getRealPosition() const;
	void setPositionFromTile(sfld::Vector2i tilePos);
	void scheduleLevelChange();
	void levelChange();
	sfld::Vector2i getTilePosition() const;
	sfld::Vector2f getCentre() const;
	virtual bool isDestroyed() const;
	SURFACE_LEVEL getSurfaceLevel() const;
	ENTITY_TYPE getType() const;
	virtual void changeWeapon(Weapon* weapon);
	virtual void changeHealth(int health);
	TileManager* getParent() const{ return parent_; }
	int getRadius() const{ return radius_; }
protected:
	void checkStatus();
	int health_;
	ENTITY_TYPE type_;
	bool toremove_;
	int radius_; //EVERYTHING IS A CIRCLE!?
	virtual std::vector<Entity*> getCollisions();
	void setTilePosition(const sfld::Vector2i& tilePosition);
	void setRealPosition(const sfld::Vector2f position);

	TileManager* parent_;

	std::unique_ptr<sf::Sprite> sprite_;
	SURFACE_LEVEL level_;
	sfld::Vector2i tilePosition_;

	float speed_;
	sfld::Vector2i targetTile_;
};