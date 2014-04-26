#pragma once

#include "stdafx.h"
#include "StateManager.h"

class SFLD : public sf::NonCopyable{
public:
	SFLD();

	void start();
	void exit();

private:
	void init();
	void runMainLoop();
	void handleSfmlEvents();
	void update(int frameTime);
	void render();

	static const int MS_PER_UPDATE = 1;

	StateManager stateManager_;
	bool exit_;
	sf::RenderWindow window_;
};