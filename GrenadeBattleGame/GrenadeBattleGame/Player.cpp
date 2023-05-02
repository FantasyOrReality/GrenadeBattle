//Classes
#include "Player.h"
#include "AssetManager.h"

enum class PhysicsType
{
		  FORWARD_EULER
		, BACKWARD_EULER
		, POSITION_VERLET
};
Player::Player()
	: OnScreenActor()
	, twoFramesOldPos(100, 300)
	, velocity(0,0)
	, acceleration(0,0)
{
	sprite.setTexture(AssetManager::RequestTexture(""));

	collisionType = CollisionType::CIRCLE;

	collisionOffset = sf::Vector2f(0.0f, 0.0f);
	collisionScale = sf::Vector2f(1.0f, 1.0f);

}

void Player::Update(sf::Time frameTime)
{
}

void Player::HandleCollision(OnScreenActor& other)
{
}

void Player::UpdateAcceleration()
{
}
