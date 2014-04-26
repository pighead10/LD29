#pragma once

#include "Vector.h"
#include "forwards.h"

#define TILE_SIZE 32

class TileManager;

class Entity{
public:
	enum SURFACE_LEVEL{
		ABOVE_GROUND,
		BELOW_GROUND
	};

	virtual void update(double frameTime);
	virtual void render(sf::RenderTarget* renderTarget);
	virtual void gotoTile(const sfld::Vector2i& tilePosition);
	virtual void move(double frameTime);
	sfld::Vector2f getCentre() const;
	virtual bool isDestroyed() const;
protected:
	bool toremove_;
	int radius_; //EVERYTHING IS A CIRCLE!?
	virtual std::vector<Entity*> getCollisions();
	void setTilePosition(const sfld::Vector2i& tilePosition);
	virtual sfld::Vector2f getRealPosition() const;
	void setRealPosition(const sfld::Vector2f position);

	TileManager* parent_;

	std::unique_ptr<sf::Sprite> sprite_;
	SURFACE_LEVEL level_;
	sfld::Vector2i tilePosition_;

	float speed_;
	sfld::Vector2i targetTile_;
};