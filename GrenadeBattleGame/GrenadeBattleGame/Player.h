#pragma once
//Default libraries
#include <iostream>

//Classes
#include "PhysicsObject.h"

//Forward declarations
class Grenade;
class LevelScreen;

class Player :
    public PhysicsObject
{
public:
    Player(std::string newPlayerIDstr, int newPlayerIDint, LevelScreen* newCurrentLevel);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void HandleCollision(OnScreenActor& other) override;

    void SetPlayerID(std::string newPlayerIDstr);
    void SetPlayerID(int newPlayerIDint);

    LevelScreen* playerLevel;


private:
    void SetAccelaration() override;

    sf::Vector2f GetPipPosition(float pipTime);

    void FireGrenade();

    //void AimGrenade(sf::Vector2f newAimTarget);
    //void FireGrenade(sf::Vector2f newAimTarget);


    sf::Vector2f twoFramesOldPos;
    sf::Sprite playerSprite;
    sf::Sound playerJumpSound;
    sf::Sound playerDeathSound;
    std::string playerIDstr;
    int playerIDint;
    bool isGrounded;
    bool isAlive;
    sf::Vector2f aimTarget;
    Grenade* playerGrenade;
    std::vector<sf::Sprite> pips;

    sf::Vector2f fireVelocity;

    sf::Time fireCooldown;
    sf::Clock fireTimer;


    
};

