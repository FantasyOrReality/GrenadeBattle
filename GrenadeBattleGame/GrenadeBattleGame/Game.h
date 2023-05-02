#pragma once

//Default libraries
#include <SFML/Graphics.hpp>

//Forward declarations
//TODO: Include the screen class


class Game
{
public:

	Game();

	void RunGameLoop();

	void EventHandling();
	void Update();
	void Draw();

	sf::RenderWindow* GetWindow();


private:

	sf::RenderWindow window;
	sf::Clock gameClock;

	//Need: Screen class
	//Screen* currentScreen;

};

