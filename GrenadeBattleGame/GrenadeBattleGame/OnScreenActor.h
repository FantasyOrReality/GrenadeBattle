#pragma once

//Default libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class CollisionType
{
	//Practical Task - Collision Geometry

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
	sf::FloatRect GetAABB();


	//Public Setters
	virtual void SetPosition(sf::Vector2f newPosition);
	virtual void SetPosition(float newX, float newY);
	void SetAlive(bool newAlive);
	void SetColliding(bool newColliding);


	bool CheckCollision(OnScreenActor other);

	sf::Vector2f CalculateCollisionDepth(OnScreenActor other);

	virtual void HandleCollision(OnScreenActor& other);




protected:


	sf::Sprite sprite;

	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;

	CollisionType collisionType;

	sf::Vector2f position;

	bool alive;



private:

	//Private Getters
	sf::Vector2f GetCollisionCentre();
	float GetCircleColliderRadius();

	//Data
	bool colliding;
};

