#include "Game.h"


Game::Game()
= default;


Game::~Game()
= default;

void Game::update(Context context)
{	
	this->context = context;
	frames++;
	frameTime += context.deltaTime;
	if (frameTime >= 100000) {
		std::cout << frames << std::endl;
		frameTime = 0;
		frames = 0;
	}
}

void Game::onEnter()
{
	// Entered the State Game

}

void Game::onLeave()
{
}