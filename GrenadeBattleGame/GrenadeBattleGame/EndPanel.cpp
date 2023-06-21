#include "EndPanel.h"
#include "AssetManager.h"
#include "EasingFunction.h"

EndPanel::EndPanel(sf::RenderWindow* newWindow, sf::Vector2f newPosition)
	: OnScreenActor()
	, title()
	, message()
	, window(newWindow)
	, animatingIn(false)
	, animationClock()
	, win()
{
	sprite.setTexture(AssetManager::RequestTexture("panel_blue"));
	sprite.setScale(5.0f, 5.0f);

	collisionOffset = sf::Vector2f(0.0f, 0.0f);
	collisionScale = sf::Vector2f(1.0f, 1.0f);
	SetPosition(newPosition);

	title.setFont(AssetManager::RequestFont("dogica"));
	title.setCharacterSize(70);
	DecideWin(win);

	message.setFont(AssetManager::RequestFont("dogica"));
	message.setCharacterSize(30);
	message.setString("Press Esc to quit");

	ResetPosition();

}

void EndPanel::Update(sf::Time frameTime)
{
	if (animatingIn)
	{
		float xPos = window->getSize().x * 0.5f - sprite.getGlobalBounds().width * 0.5f;
		float yPos = window->getSize().y;
		float finalYPos = window->getSize().y * 0.5f - sprite.getGlobalBounds().height * 0.5f;

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
	target.draw(sprite);
	target.draw(message);
	target.draw(title);
}

void EndPanel::SetPosition(sf::Vector2f newPosition)
{
	sprite.setPosition(newPosition);

	//Center the title on the x direction
	float titleX = sprite.getGlobalBounds().width * 0.5f - title.getGlobalBounds().width * 0.5f;
	title.setPosition(sf::Vector2f(newPosition.x + titleX, newPosition.y + 50));

	//Centre the message on the x and y directions
	float messageX = sprite.getGlobalBounds().width * 0.5f - message.getGlobalBounds().width * 0.5f;
	float messageY = sprite.getGlobalBounds().height * 0.5f - message.getGlobalBounds().height * 0.5f;

	message.setPosition(sf::Vector2f(newPosition.x + messageX, newPosition.y + messageY));

}

void EndPanel::StartAnimation()
{
	animatingIn = true;
	animationClock.restart();
}

void EndPanel::ResetPosition()
{
	float xPos = window->getSize().x * 0.5f - sprite.getGlobalBounds().width * 0.5f;
	float yPos = window->getSize().y;

	SetPosition(sf::Vector2f(xPos, yPos));
}

void EndPanel::DecideWin(bool win)
{
	if (win)
	{
		title.setString("YOU WIN");
	}
	else if (!win)
	{
		title.setString("YOU LOSE");
	}
}
