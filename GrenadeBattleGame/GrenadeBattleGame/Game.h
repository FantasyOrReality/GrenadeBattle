#pragma once

//Default libraries
#include <SFML/Graphics.hpp>

//Forward declarations
//TODO: Include the screen class
class Player; //temporary player declaration

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

	Player* player;

	//Need: Screen class
	//Screen* currentScreen;

};

