#pragma once

//Default libraries
#include <SFML/Graphics.hpp>

enum class CollisionType
{
	CIRCLE,
	AABB

};
class OnScreenActor
{
public:
	//Constructor
	OnScreenActor();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	//Public Getters
	sf::Vector2f GetPosition();

	//Public Setters
	virtual void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	bool CheckCollision(OnScreenActor other);
	void SetColliding(bool newColliding);

	sf::Vector2f CalculateCollisionDepth(OnScreenActor other);

	virtual void HandleCollision(OnScreenActor& other);

	void SetAlive(bool newAlive);

protected:
	sf::Sprite sprite;

	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;

	CollisionType collisionType;

	bool alive;

private:

	//Private Getters
	sf::Vector2f GetCollisionCentre();
	float GetCircleColliderRadius();
	sf::FloatRect GetAABB();

	//Data
	sf::Vector2f position;
	bool colliding;
};

