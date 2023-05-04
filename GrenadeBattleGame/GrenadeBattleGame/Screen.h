#pragma once

//Default libraries
#include <SFML/Graphics.hpp>

//Classes

//Forward declaration
class Game;

class Screen
{
public:
	Screen(Game* newGamePtr); //Constructor

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

protected:
	Game* gamePtr;

private:
};

