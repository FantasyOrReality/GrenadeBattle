#pragma once
#include "PhysicsObject.h"

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
class OnScreenActor;

class Grenade :
    public PhysicsObject
{
public:
    //Constructor
    Grenade(sf::Vector2f newPosition, sf::Vector2f newFireVelocity, int owner);

    //Update function
    void Update(sf::Time frameTime) override;

    //Draw function
    void Draw(sf::RenderTarget& target) override;

    void HandleCollision(OnScreenActor& other) override;

    

    //Public setters
    void SetOwner(int newOwner);
    void SetAlive(bool newIsAlive);

    int owner; //The number for the player that fired the grenade


private:
    //Private data

    bool isAlive;

    LevelScreen* grenadeLevel;

};

