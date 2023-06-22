#include "EndPanel.h"
#include "AssetManager.h"
#include "EasingFunction.h"

EndPanel::EndPanel(sf::RenderWindow* newWindow)
	: OnScreenActor()
	, background()
	, title()
	, message()
	, window(newWindow)
	, animatingIn(false)
	, animationClock()
	, player1win()
	, player2win()
{

	background.setTexture(AssetManager::RequestTexture("panel_blue"));
	background.setScale(6.0f, 6.0f);

	//collisionOffset = sf::Vector2f(0.0f, 0.0f);
	//collisionScale = sf::Vector2f(1.0f, 1.0f);
	//SetPosition(newPosition);

	title.setFont(AssetManager::RequestFont("dogica"));
	title.setCharacterSize(70);
	DecideWin(player1win, player2win);

	message.setFont(AssetManager::RequestFont("dogica"));
	message.setCharacterSize(30);
	message.setString("Press Esc to quit");

	ResetPosition();

}

void EndPanel::Update(sf::Time frameTime)
{
	if (animatingIn)
	{
		float xPos = window->getSize().x * 0.5f - background.getGlobalBounds().width * 0.5f;
		float yPos = window->getSize().y;
		float finalYPos = window->getSize().y * 0.5f - background.getGlobalBounds().height * 0.5f;

		sf::Vector2f begin(xPos, yPos);
		sf::Vector2f change(0, finalYPos - yPos);
		float duration = 0.2f;
		float time = animationClock.getElapsedTime().asSeconds();

		sf::Vector2f newPosition = EasingFunction::EaseOutQuad(begin, change, duration, time);
		SetPosition(newPosition);

		if (time >= duration)
		{
			SetPosition(begin + change);
			animatingIn = false;
		}
	}
}

void EndPanel::Draw(sf::RenderTarget& target)
{
	OnScreenActor::Draw(target);
	target.draw(background);
	target.draw(message);
	target.draw(title);
}

void EndPanel::SetPosition(sf::Vector2f newPosition)
{
	background.setPosition(newPosition);

	//Center the title on the x direction
	float titleX = background.getGlobalBounds().width * 0.5f - title.getGlobalBounds().width * 0.5f;
	title.setPosition(sf::Vector2f(newPosition.x + titleX, newPosition.y + 50));

	//Centre the message on the x and y directions
	float messageX = background.getGlobalBounds().width * 0.5f - message.getGlobalBounds().width * 0.5f;
	float messageY = background.getGlobalBounds().height * 0.5f - message.getGlobalBounds().height * 0.5f;

	message.setPosition(sf::Vector2f(newPosition.x + messageX, newPosition.y + messageY));

}

void EndPanel::StartAnimation()
{
	animatingIn = true;
	animationClock.restart();
}

void EndPanel::ResetPosition()
{
	float xPos = window->getSize().x * 0.5f - background.getGlobalBounds().width * 0.5f;
	float yPos = window->getSize().y;

	SetPosition(sf::Vector2f(xPos, yPos));
}

void EndPanel::DecideWin(bool player1win, bool player2win)
{
	if (player1win)
	{
		title.setString("PLAYER 2 WINS");
	}
	else if (player2win)
	{
		title.setString("PLAYER 1 WINS");
	}
}
