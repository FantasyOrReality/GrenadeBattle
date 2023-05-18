//Classes
#include "Player.h"
#include "AssetManager.h"

//Practical Task - Physics Alternatives
enum class PhysicsType
{
		  BACKWARDS_EULER //Implicit Euler
		, SYMPLECTIC_EULER //Semi-Implicit Euler
};
Player::Player(std::string newPlayerIDstr, int newPlayerIDint)
	: OnScreenActor()
	, twoFramesOldPos(100, 300)
	, velocity(0,0)
	, acceleration(0,0)
	, playerSprite()
	, playerJumpSound()
	, playerDeathSound()
	, playerIDstr(newPlayerIDstr)
	, playerIDint(newPlayerIDint)
	, playerLevel()
	, isGrounded(true)
	, isAlive(true)
	, hitboxOffset(0,0)
	, hitboxScale(1,1)
	, aimTarget(0,0)
	, pips()
	//, playerGrenade()
	, fireVelocity()
{
	sprite.setTexture(AssetManager::RequestTexture("player_" + playerIDstr + "_stand"));

	collisionType = CollisionType::CIRCLE;

	collisionOffset = sf::Vector2f(0.0f, 0.0f);
	collisionScale = sf::Vector2f(1.0f, 1.0f);

	//Add sprites to pips
	const int NUM_PIPS = 5;

	for (int i = 0; i < NUM_PIPS; ++i)
	{
		pips.push_back(sf::Sprite());
		pips[i].setTexture(AssetManager::RequestTexture("pip"));
	}
}

void Player::Update(sf::Time frameTime)
{
	//Practical Task - Gravity Prediction
	OnScreenActor::Update(frameTime);

	float pipTime = 0.0f;
	float pipTimeStep = 0.1f;

	for (int i = 0; i < pips.size(); ++i)
	{
		pips[i].setPosition(GetPipPosition(pipTime));
		pipTime += pipTimeStep;
	}

	//Get a direction for firing the grenade
	//Possible solutions: Get the player position vector and the mouse position vector and find the vector between them


	//Practical Task - Physics Alternatives
	const float DRAG_MULT = 10.0f;
	const float JOYSTICK_DRAG = 5.0f;
	const PhysicsType physics = PhysicsType::BACKWARDS_EULER;

	switch (physics)
	{
	case PhysicsType::BACKWARDS_EULER:
	{
		//IMPLICIT EULER (BACKWARD EULER) - used for accuracy

		//Update acceleration
		PlayerMovement();

		velocity += acceleration * frameTime.asSeconds();


		//drag
		if (sf::Joystick::isConnected(0) && sf::Joystick::isConnected(1))
		{
			velocity.x = velocity.x - velocity.x * DRAG_MULT * JOYSTICK_DRAG* frameTime.asSeconds();

		}
		else
		{
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

		}

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
			velocity.x = velocity.x - velocity.x * DRAG_MULT * JOYSTICK_DRAG * frameTime.asSeconds();
		}
		else
		{
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

		}
		SetPosition(GetPosition() + velocity * frameTime.asSeconds());

		//Move the player
		PlayerMovement();
	}
	break;
	}
}

void Player::Draw(sf::RenderTarget& target)
{
	OnScreenActor::Draw(target);

	//Draw pips
	for (int i = 0; i < pips.size(); ++i)
	{
		target.draw(pips[i]);
	}
}

void Player::HandleCollision(OnScreenActor& other)
{
	//Practical Task - Physics Alternatives
	sf::Vector2f depth = CalculateCollisionDepth(other);
	sf::Vector2f newPosition = GetPosition();
	const float JUMPSPEED = 0; //No jump required right now

	if (abs(depth.x) < abs(depth.y))
	{
		//Move in x direction
		newPosition.x += depth.x;
		velocity.x = 0;
		acceleration.x = 0;
	}
	else
	{
		//Move in y direction
		newPosition.y += depth.y;
		velocity.y = 0;
		acceleration.y = 0;

		//Collision from above
		if (depth.y < 0)
		{
			
			velocity.y = -JUMPSPEED;
		}
	}

	SetPosition(newPosition);
}

void Player::PlayerMovement()
{
	//Practical Task - Physics Alternatives
	const float ACCEL = 5000.0f;
	const float JOYSTICK_FACTOR = 0.1f;
	


	acceleration.x = 0;
	acceleration.y = gravity;
	if (playerIDint == 1)
	{
		if (sf::Joystick::isConnected(0))
		{
			acceleration.x = sf::Joystick::getAxisPosition(0, sf::Joystick::X)*ACCEL*JOYSTICK_FACTOR;

			fireVelocity.x = sf::Joystick::getAxisPosition(0, sf::Joystick::U)/ JOYSTICK_FACTOR;
			fireVelocity.y = sf::Joystick::getAxisPosition(0, sf::Joystick::V) / JOYSTICK_FACTOR;
		}
		else if (!sf::Joystick::isConnected(0))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				acceleration.x = -ACCEL;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				acceleration.x = ACCEL;

			}
		}
	}

	if (playerIDint == 2)
	{
		if (sf::Joystick::isConnected(1))
		{
			acceleration.x = sf::Joystick::getAxisPosition(1, sf::Joystick::X) * ACCEL * JOYSTICK_FACTOR;

			fireVelocity.x = sf::Joystick::getAxisPosition(1, sf::Joystick::U) / JOYSTICK_FACTOR;
			fireVelocity.y = sf::Joystick::getAxisPosition(1, sf::Joystick::V) / JOYSTICK_FACTOR;
		}
		else if (!sf::Joystick::isConnected(1))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				acceleration.x = -ACCEL;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				acceleration.x = ACCEL;

			}
		}
	}

}

sf::Vector2f Player::GetPipPosition(float pipTime)
{
	//Practical Task - Gravity Prediction
	sf::Vector2f pipPosition;
	

	//pipPosition = sf::Vector2f(0.0f, 1000.0f)*pipTime*pipTime
		//+ sf::Vector2f(500.0f, -1000.0f)*pipTime
		//+ sf::Vector2f(500.0f ,500.0f);

	pipPosition = sf::Vector2f(0.0f, gravity / 2.0f) * pipTime * pipTime
		+ fireVelocity * pipTime
		+ GetPosition();

	return pipPosition;
}

void Player::SetPlayerID(std::string newPlayerIDstr)
{
	playerIDstr = newPlayerIDstr;
	sprite.setTexture(AssetManager::RequestTexture("player_"+ playerIDstr + "_stand"));

}

void Player::SetPlayerID(int newPlayerIDint)
{
	playerIDint = newPlayerIDint;
}


