#pragma once

//Default libraries
#include <SFML/Graphics.hpp>
#include <iostream>

//Classes
#include "Screen.h" //Parent class
//Include all things in the level
#include "OnScreenActor.h"
#include "EndPanel.h"

//Forward declarations
class Game;
class Platform;
class Player;
class Grenade;

class LevelScreen :
    public Screen
{
public:
    LevelScreen(Game* newGamePtr);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void FireGrenade(sf::Vector2f firePosition, sf::Vector2f fireVelocity, int grenadeOwner);

    void TriggerEndState(bool player1win, bool player2win);

    bool CheckGrenadeAlive(bool isGrenadeAlive);

    

protected:
    

private:
    

    Player* player1;
    Player* player2;

    EndPanel endPanel;

    bool gameRunning;
    bool grenadeAlive;
    bool player1Win;
    bool player2Win;
    std::vector<Platform*> platformTiles;
    std::vector<Grenade*> grenadeVector;

    sf::Font gameFont;
    sf::Text scoreDisplay;
    int scoreValue;

    sf::View cameraView;

    sf::Music gameMusic;

    int currentLevel;

    std::string levelIDstr;
    int levelIDint;

};

