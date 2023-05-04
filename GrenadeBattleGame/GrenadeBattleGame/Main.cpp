//Default libraries
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

//Classes
#include "Game.h"
#include "AssetManager.h"

int main()
{

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