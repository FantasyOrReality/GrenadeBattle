#include "PhysicsObject.h"

//Practical Task - Physics Alternatives
enum class PhysicsType
{
	BACKWARDS_EULER //Implicit Euler
	, SYMPLECTIC_EULER //Semi-Implicit Euler
};

PhysicsObject::PhysicsObject()
	: OnScreenActor()
	, gravity(1000.0f)
	, velocity()
	, acceleration(0, 0)
	, applyDrag(true)
{

}

void PhysicsObject::Update(sf::Time frameTime)
{
	OnScreenActor::Update(frameTime);

	//Practical Task - Physics Alternatives
	const float DRAG_MULT = 10.0f;
	const float JOYSTICK_DRAG = 5.0f;
	const PhysicsType physics = PhysicsType::BACKWARDS_EULER;

	switch (physics)
	{
	case PhysicsType::BACKWARDS_EULER:
	{
		//IMPLICIT EULER (BACKWARD EULER) - used for accuracy
		velocity += acceleration * frameTime.asSeconds();

		//drag
		if (sf::Joystick::isConnected(0) && sf::Joystick::isConnected(1))
		{
			if (applyDrag)
			{
				velocity.x = velocity.x - velocity.x * DRAG_MULT * JOYSTICK_DRAG * frameTime.asSeconds();
			}
		}
		else
		{
			if (applyDrag)
			{
				velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

			}
		}
		SetAccelaration();
		SetPosition(GetPosition() + velocity * frameTime.asSeconds());
	}
	break;
	case PhysicsType::SYMPLECTIC_EULER:
	{
		//SEMI-IMPLICIT EULER (SYMPLECTIC EULER) - Used for ease of implementation
		velocity += acceleration * frameTime.asSeconds();

		//drag
		if (sf::Joystick::isConnected(0) && sf::Joystick::isConnected(1))
		{
			if (applyDrag)
			{
				velocity.x = velocity.x - velocity.x * DRAG_MULT * JOYSTICK_DRAG * frameTime.asSeconds();

			}
			
		}
		else
		{
			if (applyDrag)
			{
				velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

			}
			
		}
		SetAccelaration();

		//Move the player
		//PlayerMovement();
	}
	break;
	}
}

void PhysicsObject::SetVelocity(sf::Vector2f newVelocity)
{
	velocity = newVelocity;

}

void PhysicsObject::SetAccelaration()
{
	acceleration.x = 0;
	acceleration.y = gravity;

}
