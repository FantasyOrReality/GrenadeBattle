#pragma once
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

class LevelScreen;
class Player;

class Grenade :
    public OnScreenActor
{
public:
    //Constructor
    Grenade(sf::Vector2f position, sf::Vector2f fireVelocity, int owner);

    //Update function
    void Update(sf::Time frameTime) override;

    //Draw function
    void Draw(sf::RenderTarget& target) override;

    //Fire the grenade in a position at a velocity
    void FireGrenade(sf::Vector2f firePosition, sf::Vector2f fireVelocity, Player* newPlayerPtr);

    //Public setters
    void SetOwner(int newOwner);
    void SetCooldown(sf::Clock newFireCooldown);


private:

    //Private setters
    void SetVelocity(sf::Vector2f newVelocity);
    void SetPosition(sf::Vector2f newPosition) override;
    void SetPosition(float newX, float newY) override;

    //Private data
    sf::Sprite grenadeSprite; //The object used as the sprite
    sf::Vector2f velocity; //The velocity vector for how fast the grenade travels
    sf::Vector2f position; //The position vector to know where the grenade is
    int owner; //The number for the player that fired the grenade
    Player* playerPtr; //The player pointer used in the firing function

    sf::Clock fireCooldown; //The amount of time between firing grenades (so the players don't spam the button)



};

