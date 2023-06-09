#include "Platform.h"
#include "AssetManager.h"

Platform::Platform(sf::Vector2f newPosition)
	: OnScreenActor()
	, currentLevel()
{

	sprite.setTexture(AssetManager::RequestTexture("tile"));

	collisionOffset = sf::Vector2f(0.0f, 0.0f);
	collisionScale = sf::Vector2f(1.0f, 1.0f);
	SetPosition(newPosition);

}
