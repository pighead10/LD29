#include "stdafx.h"
#include "GameState.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "TileManager.h"
#include "Player.h"
#include "RandomAi.h"
#include "WeaponGiver.h"
#include "SpinSlashWeapon.h"
#include "UpwardsStabWeapon.h"
#include "SpringPlacerWeapon.h"

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

	resourceManager_.setDirectory("media/images/");
	resourceManager_.load("test", "test.png");
	resourceManager_.load("testai", "testai.png");
	resourceManager_.load("testcollided", "testcollided.png");
	resourceManager_.load("hole", "hole.png");
	resourceManager_.load("spinslash", "spinslash.png");
	resourceManager_.load("weapongiver", "weapongiver.png");
	resourceManager_.load("upwardstab", "upwardstab.png");
	resourceManager_.load("spring", "spring.png");
	resourceManager_.load("grassbg", "grassbg.png");
	resourceManager_.load("stonebg", "stonebg.png");

	wep = std::unique_ptr<Weapon>(new SpringPlacerWeapon(&resourceManager_,NULL));

	tileManager_ = std::unique_ptr<TileManager>(new TileManager(&resourceManager_));
	tileManager_->scheduleEntityAdd(new Player(tileManager_.get(),new sf::Sprite(resourceManager_.get("test")),&resourceManager_), Entity::ABOVE_GROUND);
	tileManager_->scheduleEntityAdd(new RandomAi(tileManager_.get(), new sf::Sprite(resourceManager_.get("testai")), Entity::ABOVE_GROUND, sfld::Vector2i(10, 1)), Entity::ABOVE_GROUND);
	tileManager_->scheduleEntityAdd(new RandomAi(tileManager_.get(), new sf::Sprite(resourceManager_.get("testai")), Entity::ABOVE_GROUND, sfld::Vector2i(10, 5)), Entity::ABOVE_GROUND);
	tileManager_->scheduleEntityAdd(new RandomAi(tileManager_.get(), new sf::Sprite(resourceManager_.get("testai")), Entity::BELOW_GROUND, sfld::Vector2i(10, 1)), Entity::BELOW_GROUND);
	tileManager_->scheduleEntityAdd(new WeaponGiver(tileManager_.get(), sfld::Vector2i(15, 15), wep.get(), Entity::ABOVE_GROUND, new sf::Sprite(resourceManager_.get("weapongiver"))),Entity::ABOVE_GROUND);
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