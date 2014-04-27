#pragma once

#include "BaseState.h"
#include "ResourceManager.h"
#include "SpinSlashWeapon.h"

class TileManager;

class GameState : public BaseState{
public:
	GameState();
	~GameState();
	void sfmlEvent(sf::Event evt);

	void start();
	void pause();
	void resume();
	void exit();

	void update(int frameTime);
	void render(sf::RenderTarget* target);
private:
	std::unique_ptr<SpinSlashWeapon> spinWep;

	std::unique_ptr<TileManager> tileManager_;
	ResourceManager<sf::Texture,std::string> resourceManager_;
};