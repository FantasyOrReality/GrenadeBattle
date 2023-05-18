#pragma once
//Default libraries
#include <iostream>

//Classes
#include "OnScreenActor.h"

//Forward declarations
//class Grenade;
class LevelScreen;

class Player :
    public OnScreenActor
{
public:
    Player(std::string newPlayerIDstr, int newPlayerIDint);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void HandleCollision(OnScreenActor& other) override;

    void SetPlayerID(std::string newPlayerIDstr);
    void SetPlayerID(int newPlayerIDint);

private:
    void PlayerMovement();

    sf::Vector2f GetPipPosition(float pipTime);

    //void AimGrenade(sf::Vector2f newAimTarget);
    //void FireGrenade(sf::Vector2f newAimTarget);


    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    sf::Sprite playerSprite;
    sf::Sound playerJumpSound;
    sf::Sound playerDeathSound;
    std::string playerIDstr;
    int playerIDint;
    LevelScreen* playerLevel;
    bool isGrounded;
    bool isAlive;
    sf::Vector2f hitboxOffset;
    sf::Vector2f hitboxScale;
    sf::Vector2f aimTarget;
    //Grenade* playerGrenade;
    std::vector<sf::Sprite> pips;

    sf::Vector2f fireVelocity;
    
};

