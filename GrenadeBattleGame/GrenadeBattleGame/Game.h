#pragma once

//Default libraries
#include <SFML/Graphics.hpp>

#include "LevelScreen.h"

//Forward declarations
class Screen; 

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

	
	Screen* currentScreen;

};

