//Default libraries
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

//Classes
#include "Game.h"
#include "AssetManager.h"

int main()
{
    //Default template
    /*
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    */

    //Initialise the random number generator
    srand(time(NULL));

    //Create the game
    Game gameInstance; //default constructor

    //Will not end until game over
    gameInstance.RunGameLoop();

    //If we get here, the loop exited, so the game is over

    //Clean up assets
    AssetManager::DestroyAllAssets();

    //End the program by returning an int
    return 0;
}