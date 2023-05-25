#include "Grenade.h"
#include "AssetManager.h"

/*
1. Create a Grenade Class
    - PhysicsObject (or similar)
    - Function to fire it at a specific velocity (set its velocity)
    - SetPosition (may already have this)
    - An indication of which player it belongs to (int)


2. Add a vector of grenades to Level class
    - Draw them
    - Update them
    - Public function to fire one, that includes a position,
        a firing velocity, and what player it is. This will need
        to create a grenade and add it to the vector.


3. Make the player fire grenades
    - The player must know about Level - give them a pointer
        set at player creation time
    - In update, check if the button was pressed, if so, fire.
    - Add a timer so the player can't fire too fast
*/

enum class PhysicsType
{
    BACKWARDS_EULER //Implicit Euler
    , SYMPLECTIC_EULER //Semi-Implicit Euler
};

Grenade::Grenade(sf::Vector2f position, sf::Vector2f fireVelocity, int owner)
    : OnScreenActor()
    , grenadeSprite()
    , velocity()
    , position()
    , owner()
    , playerPtr(nullptr)
    , fireCooldown()
{
    sprite.setTexture(AssetManager::RequestTexture("grenade"));

    collisionType = CollisionType::CIRCLE;

    collisionOffset = sf::Vector2f(0.0f, 0.0f);
    collisionScale = sf::Vector2f(1.0f, 1.0f);
}

void Grenade::Update(sf::Time frameTime)
{
    OnScreenActor::Update(frameTime);

}

void Grenade::Draw(sf::RenderTarget& target)
{
    OnScreenActor::Draw(target);

}

void Grenade::FireGrenade(sf::Vector2f firePosition, sf::Vector2f fireVelocity, Player* newPlayerPtr)
{
}

void Grenade::SetOwner(int newOwner)
{
    owner = newOwner;
}

void Grenade::SetCooldown(sf::Clock newFireCooldown)
{

    //sf::Time cooldownPeriod = sf::seconds(1.5f);
    //sf::Clock fireCooldown = (cooldownPeriod.asSeconds(); //The amount of time between firing grenades (so the players don't spam the button)


}

void Grenade::SetVelocity(sf::Vector2f newVelocity)
{
    velocity = newVelocity;

}

void Grenade::SetPosition(sf::Vector2f newPosition)
{
    position = newPosition;

}

void Grenade::SetPosition(float newX, float newY)
{
    position.x = newX;
    position.y = newY;
}
