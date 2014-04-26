#include "stdafx.h"
#include "GameState.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "TileManager.h"
#include "Player.h"
#include "RandomAi.h"

GameState::GameState() = default;
GameState::~GameState() = default;

void GameState::sfmlEvent(sf::Event evt){
	switch(evt.type){
	case sf::Event::Closed:
		getParent().pop();
		break;
	default:
		break;
	}
}

void GameState::start(){ 
	//		-fix collision problem where two things moving into each other will be pushed
	//		-additional testing of collisions

	resourceManager_.setDirectory("media/images/");
	resourceManager_.load("test", "test.png");
	resourceManager_.load("testai", "testai.png");
	resourceManager_.load("testcollided", "testcollided.png");
	tileManager_ = std::unique_ptr<TileManager>(new TileManager());
	tileManager_->add(new Player(tileManager_.get(),new sf::Sprite(resourceManager_.get("test")),&resourceManager_), Entity::ABOVE_GROUND);
	tileManager_->add(new RandomAi(tileManager_.get(), new sf::Sprite(resourceManager_.get("testai")), Entity::ABOVE_GROUND,sfld::Vector2i(10,1)), Entity::ABOVE_GROUND);
	tileManager_->add(new RandomAi(tileManager_.get(), new sf::Sprite(resourceManager_.get("testai")), Entity::ABOVE_GROUND, sfld::Vector2i(10, 5)), Entity::ABOVE_GROUND);
	tileManager_->add(new RandomAi(tileManager_.get(), new sf::Sprite(resourceManager_.get("testai")), Entity::ABOVE_GROUND, sfld::Vector2i(10, 1)), Entity::BELOW_GROUND);
}

void GameState::pause(){
}


void GameState::resume(){
}

void GameState::exit(){
}

void GameState::update(int frameTime){
	tileManager_->updateAll(frameTime);
}

void GameState::render(sf::RenderTarget* target){
	tileManager_->renderAll(target);
}