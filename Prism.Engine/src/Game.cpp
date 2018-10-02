#include "Game.h"
#include "Context.h"


Game::Game()
= default;


Game::~Game()
= default;


void Game::update(Context context)
{
	this->context = context;
}

void Game::onEnter()
{
	// Entered the State Game

}

void Game::onLeave()
{
}
