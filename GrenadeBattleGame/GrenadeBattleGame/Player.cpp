//Classes
#include "Player.h"
#include "AssetManager.h"
#include "LevelScreen.h"
#include "Screen.h"
#include "Grenade.h"

//Practical Task - Physics Alternatives
enum class PhysicsType
{
		  BACKWARDS_EULER //Implicit Euler
		, SYMPLECTIC_EULER //Semi-Implicit Euler
};
Player::Player(std::string newPlayerIDstr, int newPlayerIDint, LevelScreen* newCurrentLevel)
	: OnScreenActor()
	, twoFramesOldPos(100, 300)
	, velocity(0,0)
	, acceleration(0,0)
	, playerSprite()
	, playerJumpSound()
	, playerDeathSound()
	, playerIDstr(newPlayerIDstr)
	, playerIDint(newPlayerIDint)
	, playerLevel(newCurrentLevel)
	, isGrounded(true)
	, isAlive(true)
	, hitboxOffset(0,0)
	, hitboxScale(1,1)
	, aimTarget(0,0)
	, pips()
	, playerGrenade(nullptr)
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

	//Practical Task - Physics Alternatives
	const float DRAG_MULT = 10.0f;
	const float JOYSTICK_DRAG = 5.0f;
	const PhysicsType physics = PhysicsType::BACKWARDS_EULER;

	if (sf::Joystick::isButtonPressed(0, 0))
	{
		playerLevel->FireGrenade(GetPosition() + velocity * frameTime.asSeconds(), sf::Vector2f(velocity.x, velocity.y), 1); //Position, velocity, owner
	}

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

	//if (sf::Joystick::isButtonPressed(0, 0))
	//{
		//playerLevel->FireGrenade(, , 1); //Position, velocity, owner
	//}

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
	//const float JUMPSPEED = 0; //No jump required right now

	if (abs(depth.x) < abs(depth.y))
	{
		//Move in x direction
		newPosition.x += depth.x*2.0f;
		velocity.x = 0;
		acceleration.x = 0;
	}
	else
	{
		//Move in y direction
		newPosition.y += depth.y*2.0f;
		velocity.y = 0;
		acceleration.y = 0;

		//Collision from above
		if (depth.y < 0)
		{
			
			//velocity.y = -JUMPSPEED;
		}
	}

	SetPosition(newPosition);
}

void Player::PlayerMovement()
{
	//Practical Task - Physics Alternatives
	const float ACCEL = 5000.0f;
	const float JOYSTICK_FACTOR = 0.1f;
	const float DEADZONE = 10.0f;


	acceleration.x = 0;
	acceleration.y = gravity;

	if (sf::Joystick::isConnected(playerIDint-1))
	{
		float joystickX = sf::Joystick::getAxisPosition(playerIDint-1, sf::Joystick::X);
		float joystickU = sf::Joystick::getAxisPosition(playerIDint - 1, sf::Joystick::U);
		float joystickV = sf::Joystick::getAxisPosition(playerIDint - 1, sf::Joystick::V);

		if (joystickX > DEADZONE || joystickX< -DEADZONE)
		{
			acceleration.x = joystickX * ACCEL * JOYSTICK_FACTOR;

		}
		if (joystickU > DEADZONE || joystickU < -DEADZONE)
		{
			fireVelocity.x = joystickU / JOYSTICK_FACTOR;
		}
		if (joystickV > DEADZONE || joystickV < -DEADZONE)
		{
			fireVelocity.y = joystickV / JOYSTICK_FACTOR;
		}
	}
	else if (!sf::Joystick::isConnected(playerIDint - 1))
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


