#pragma once
//Default libraries
#include <iostream>

//Classes
#include "OnScreenActor.h"

//class Grenade;
//class LevelScreen

class Player :
    public OnScreenActor
{
public:
    Player();

    void Update(sf::Time frameTime) override;

    void HandleCollision(OnScreenActor& other) override;

    void GetCurrentLevel(/*LevelScreen* newPlayerLevel*/ );

    void PlayerMovement();
    void PlayerAutoJump();
    void PlayerDeath();
    void SetGrounded(bool newIsGrounded);

private:

    void AimGrenade(sf::Vector2f newAimTarget);
    void FireGrenade(sf::Vector2f newAimTarget);


    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    sf::Sprite playerSprite;
    sf::Sound playerJumpSound;
    sf::Sound playerDeathSound;
    std::string playerIDstr;
    int playerIDint;
    //LevelScreen* playerLevel;
    bool isGrounded;
    bool isAlive;
    sf::Vector2f hitboxOffset;
    sf::Vector2f hitboxScale;
    sf::Vector2f aimTarget;
    //Grenade* playerGrenade;
    
};

