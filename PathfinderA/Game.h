#pragma once
#include "GameState.h"

class Game
{
private:

	//Core
	sf::RenderWindow mWindow;


	//GameState
	GameState* gameState = nullptr;

private:

	//Core private
	void update(const float& dt);
	void render();
	void processEvents();


public:

	Game();
	~Game();

	//Core public
	void run();
};

