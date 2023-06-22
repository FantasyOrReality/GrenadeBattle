//Default libraries
#include <algorithm>

//Classes
#include "OnScreenActor.h"
#include "VectorHelper.h"

OnScreenActor::OnScreenActor()
	: sprite()
	, position(0,0)
	, colliding(false)
	, collisionOffset()
	, collisionScale()
	, collisionType(CollisionType::AABB)
	, alive(true)
{
	
}

void OnScreenActor::Update(sf::Time frameTime)
{

}

void OnScreenActor::Draw(sf::RenderTarget& target)
{
	if (!alive)
	{
		return;
	}

	//Practical Task - Collision Geometry

	target.draw(sprite);
	
	bool drawCollider = false;

	
	if (drawCollider)
	{
		switch (collisionType)
		{
		case CollisionType::AABB:
		{
			sf::RectangleShape rectangle;
			sf::FloatRect bounds = GetAABB();
			rectangle.setPosition(bounds.left, bounds.top);
			rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));

			sf::Color collisionColour = sf::Color::Green;

			// turn red if a collision happens
			if (colliding)
			{
				collisionColour = sf::Color::Red;
			}
			collisionColour.a = 100;
			rectangle.setFillColor(collisionColour);

			target.draw(rectangle);
		}
		break;

		case CollisionType::CIRCLE:
		{
			sf::CircleShape circle;

			sf::Vector2f shapePosition = GetCollisionCentre();
			float circleRadius = GetCircleColliderRadius();
			shapePosition.x -= circleRadius;
			shapePosition.y -= circleRadius;


			circle.setPosition(shapePosition);
			circle.setRadius(circleRadius);
			sf::Color collisionColour = sf::Color::Green;

			// turn red if a collision happens
			if (colliding)
			{
				collisionColour = sf::Color::Red;
			}
			collisionColour.a = 100;
			circle.setFillColor(collisionColour);

			target.draw(circle);
		}
		break;

		default:
			break;
		}
	}
	
	
}

sf::Vector2f OnScreenActor::GetPosition()
{
	return position;
}

void OnScreenActor::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}

void OnScreenActor::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

bool OnScreenActor::CheckCollision(OnScreenActor other)
{
	if (!alive || !other.alive)
	{
		return false;
	}

	//Practical Task - Collision Geometry

	return GetAABB().intersects(other.GetAABB());

	/*
	switch (collisionType)
	{
	case CollisionType::AABB:
	{
		if (other.collisionType == CollisionType::AABB)
		{
			return GetAABB().intersects(other.GetAABB());
		}
		else
		{
			sf::Vector2f nearestPointToCircle = other.GetCollisionCentre();
			sf::FloatRect thisAABB = GetAABB();

			nearestPointToCircle.x = fmaxf(thisAABB.left, fminf(nearestPointToCircle.x, thisAABB.left + thisAABB.width));
			nearestPointToCircle.y = fmaxf(thisAABB.top, fminf(nearestPointToCircle.y, thisAABB.top + thisAABB.height));
			sf::Vector2f displacement = nearestPointToCircle - other.GetCollisionCentre();
			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = other.GetCircleColliderRadius();
			return squareDistance <= circleRadius * circleRadius;
		}
	}
	break;

	case CollisionType::CIRCLE:
	{
		if (other.collisionType == CollisionType::CIRCLE)
		{
			//get the vector representing the displacement between the two circles
			sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();

			//Get the magnitude of that vector, which is how far apart the circle centres
			float squareDistance = VectorHelper::SquareMagnitude(displacement);

			//Compare that to the combined radii of the two circles
			float combinedRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();

			return squareDistance <= combinedRadii * combinedRadii;
		}
		else
		{
			sf::Vector2f nearestPointToCircle = GetCollisionCentre();
			sf::FloatRect otherAABB = other.GetAABB();

			nearestPointToCircle.x = fmaxf(otherAABB.left, fminf(nearestPointToCircle.x, otherAABB.left + otherAABB.width));
			nearestPointToCircle.y = fmaxf(otherAABB.top, fminf(nearestPointToCircle.y, otherAABB.top + otherAABB.height));

			sf::Vector2f displacement = nearestPointToCircle - GetCollisionCentre();
			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = GetCircleColliderRadius();
			return squareDistance <= circleRadius * circleRadius;

		}
	}
	break;

	default:
	{
		return GetAABB().intersects(other.GetAABB());
	}
	break;
	}
	*/


}

void OnScreenActor::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

sf::Vector2f OnScreenActor::CalculateCollisionDepth(OnScreenActor other)
{
	// Practical Task - Collision Geometry
	sf::FloatRect thisAABB = GetAABB();
	sf::FloatRect otherAABB = other.GetAABB();

	sf::Vector2f thisCentre = GetCollisionCentre();
	sf::Vector2f otherCentre = other.GetCollisionCentre();

	sf::Vector2f minDistance;
	minDistance.x = thisAABB.width * 0.5f + otherAABB.width * 0.5f;
	minDistance.y = thisAABB.height * 0.5f + otherAABB.height * 0.5f;

	sf::Vector2f actualDistance = otherCentre - thisCentre;

	if (actualDistance.x < 0)
	{
		minDistance.x = -minDistance.x;
	}
	if (actualDistance.y < 0)
	{
		minDistance.y = -minDistance.y;
	}

	return actualDistance - minDistance;
}

void OnScreenActor::HandleCollision(OnScreenActor& other)
{
	//Do nothing, handled in child class
}

void OnScreenActor::SetAlive(bool newAlive)
{
	alive = newAlive;
}

sf::Vector2f OnScreenActor::GetCollisionCentre()
{
	sf::Vector2f centre = position;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	centre.x += bounds.width * 0.5f;
	centre.y += bounds.height * 0.5f;

	centre.x += collisionOffset.x;
	centre.y += collisionOffset.y;

	return centre;
}

float OnScreenActor::GetCircleColliderRadius()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;


	if (bounds.width > bounds.height)
	{
		return bounds.width * 0.5f;
	}
	else
	{
		return bounds.height * 0.5f;

	}
}

sf::FloatRect OnScreenActor::GetAABB()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	sf::Vector2f centre = GetCollisionCentre();

	bounds.left = centre.x - bounds.width * 0.5f;
	bounds.top = centre.y - bounds.height * 0.5f;

	return bounds;
}
