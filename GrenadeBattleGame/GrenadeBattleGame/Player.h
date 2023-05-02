#pragma once

//Classes
#include "OnScreenActor.h"

class Player :
    public OnScreenActor
{
public:
    Player();

    void Update(sf::Time frameTime) override;

    void HandleCollision(OnScreenActor& other) override;

private:

    void UpdateAcceleration();


    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};

