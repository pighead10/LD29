#include "stdafx.h"
#include "SFLD.h"
#include "GameState.h"

SFLD::SFLD():stateManager_(this){
}

void SFLD::start(){
	init();
	runMainLoop();
}

void SFLD::exit(){
	exit_ = true;
}

void SFLD::init(){
	exit_ = false;
	sf::VideoMode vm(1024,768);
	window_.create(vm,"SFLD");
	stateManager_.push(new GameState());
}


void SFLD::runMainLoop(){
	sf::Clock clock;
	int previous = clock.getElapsedTime().asMilliseconds();
	int lag = 0;

	while(!exit_){
		int current = clock.getElapsedTime().asMilliseconds();
		int elapsed = current - previous;
		previous = current;
		lag += elapsed;

		handleSfmlEvents();

		while(lag >= MS_PER_UPDATE && !exit_){
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}

		render();
	}
}

void SFLD::handleSfmlEvents(){
	sf::Event evt;
	while(window_.pollEvent(evt)){
		//handle application-wide sfml events...
		stateManager_.sfmlEvent(evt);
	}
}

void SFLD::update(int frameTime){
	//application-wide per frame things...
	stateManager_.update(frameTime);
}

void SFLD::render(){
	if(!exit_){
		window_.clear(sf::Color::White);
		//application-wide rendering effects...
		stateManager_.render(&window_);
		window_.display();
	}
}
