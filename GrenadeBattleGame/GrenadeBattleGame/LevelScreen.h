#pragma once

//Default libraries
#include <SFML/Graphics.hpp>
#include <iostream>

//Classes
#include "Screen.h" //Parent class
//Include all things in the level
#include "OnScreenActor.h"
#include "Player.h"

//TODO:Include grenade class

//Forward declarations
class Game;
class Platform;

class LevelScreen :
    public Screen
{
public:
    LevelScreen(Game* newGamePtr);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;


private:
    std::string levelIDstr;
    int levelIDint;

    Player* player1;
    Player* player2;
    bool gameRunning;

    std::vector<Platform*> platformTiles;

    sf::Font gameFont;
    sf::Text scoreDisplay;
    int scoreValue;

    sf::View cameraView;

    sf::Music gameMusic;

    int currentLevel;

};

