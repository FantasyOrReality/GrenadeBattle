#pragma once

//Base class
#include "OnScreenActor.h"

//Default libraries
#include <SFML/Graphics.hpp>

class EndPanel :
    public OnScreenActor
{

public:
	EndPanel(sf::RenderWindow* newWindow);

    void Update(sf::Time frameTime) override;
	void Draw(sf::RenderTarget& target) override;

	void SetPosition(sf::Vector2f newPosition) override;

	void StartAnimation();
	void ResetPosition();

	void DecideWin(bool newPlayer1win, bool newPlayer2win);


	
private:
	sf::Sprite background;
	sf::Text title;
	sf::Text message;
	sf::RenderWindow* window;

	bool animatingIn;
	sf::Clock animationClock;

	bool player1win;
	bool player2win;
};

