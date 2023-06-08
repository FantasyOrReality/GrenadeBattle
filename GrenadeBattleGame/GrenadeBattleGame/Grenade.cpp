#include "Grenade.h"
#include "AssetManager.h"
#include "VectorHelper.h"
#include "OnScreenActor.h"

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

    collisionType = CollisionType::AABB;

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

void Grenade::HandleCollision(OnScreenActor& other)
{
    //Practical Task - Physics Alternatives
    sf::Vector2f depth = CalculateCollisionDepth(other);
    sf::Vector2f newPosition = GetPosition();

    sf::Vector2f topRight = sf::Vector2f(other.GetAABB().left + other.GetAABB().width, other.GetAABB().top);
    sf::Vector2f bottomLeft = sf::Vector2f(other.GetAABB().left, other.GetAABB().top+ other.GetAABB().height);
    sf::Vector2f topLeft = sf::Vector2f(other.GetAABB().left, other.GetAABB().top);
    //const float JUMPSPEED = 0; //No jump required right now

    if (abs(depth.x) < abs(depth.y))
    {
        //Move in x direction
        newPosition.x += depth.x * 2.0f;
        velocity = VectorHelper::GetReflection(newPosition, VectorHelper::Normalise(VectorHelper::GetNormal(topLeft - bottomLeft)));

        acceleration.x = 0;
    }
    else
    {
        //Move in y direction
        newPosition.y += depth.y * 2.0f;
        velocity = VectorHelper::GetReflection(newPosition, VectorHelper::Normalise(VectorHelper::GetNormal(topRight - topLeft)));

        acceleration.y = 0;

        //Collision from above
        if (depth.y < 0)
        {

            //velocity.y = -JUMPSPEED;
        }
    }

    SetPosition(newPosition);
}










