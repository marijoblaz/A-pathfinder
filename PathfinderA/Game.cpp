#include "Game.h"

void Game::update(const float &dt)
{
    this->gameState->update(dt);
}

void Game::render()
{
    this->mWindow.clear();
    this->gameState->render(mWindow);
    this->mWindow.display();
}

void Game::processEvents()
{
    sf::Event event;
    while (this->mWindow.pollEvent(event))
    {

        if (event.type == sf::Event::Closed) {
            this->mWindow.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            this->mWindow.close();
        }
            
    }
}

Game::Game() : mWindow(sf::VideoMode(1280, 720, 32), "SFML Window", sf::Style::Close)
{
    this->gameState = new GameState(&this->mWindow);
    this->mWindow.setFramerateLimit(60);
}

Game::~Game()
{
    delete this->gameState;
}

void Game::run()
{
    sf::Clock clock;
    /* initialize random seed: */
    srand(time(NULL));

    while (this->mWindow.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        this->processEvents();
        this->update(deltaTime.asSeconds());
        this->render();

    }
}
