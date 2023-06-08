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

Grenade::Grenade(sf::Vector2f newPosition, sf::Vector2f newFireVelocity, int owner)
    : PhysicsObject()
    , owner(owner)
{
    sprite.setTexture(AssetManager::RequestTexture("grenade"));

    SetPosition(newPosition);
    velocity = newFireVelocity;

    applyDrag = false;

    collisionType = CollisionType::CIRCLE;

    collisionOffset = sf::Vector2f(0.0f, 0.0f);
    collisionScale = sf::Vector2f(0.5f, 0.5f);
}

void Grenade::Update(sf::Time frameTime)
{
    PhysicsObject::Update(frameTime);

    //SetPosition(GetPosition() + fireVelocity * frameTime.asSeconds());

    //SetVelocity(fireVelocity);
    //Grenade movement


}

void Grenade::Draw(sf::RenderTarget& target)
{
    PhysicsObject::Draw(target);

}

void Grenade::SetOwner(int newOwner)
{
    owner = newOwner;
}










