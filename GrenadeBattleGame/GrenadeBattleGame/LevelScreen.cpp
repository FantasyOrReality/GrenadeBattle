//Default libraries
#include <fstream>
#include <iostream>

//Classes
#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "Game.h"




LevelScreen::LevelScreen(Game* newGamePtr)
	: Screen(newGamePtr)
	, levelIDstr()
	, levelIDint()
	, player1()
	, player2()
	, gameRunning(true)
	, platformTiles()
	, gameFont()
	, scoreDisplay()
	, scoreValue(0)
	, cameraView()
	, gameMusic()
	, currentLevel(1)
{
	player1->SetPlayerID("1"); //set the player ID to use when setting textures
	player2->SetPlayerID("2"); //set the player ID to use when setting textures

	player1->SetPlayerID(1); //set the player ID to use when setting controls
	player2->SetPlayerID(2); //set the player ID to use when setting controls

	

	player1->SetPosition(300.0f, 700.0f);
	player2->SetPosition(700.0f, 700.0f);

	platformTiles.push_back(new Platform(sf::Vector2f(300.0f, 900.0f)));

}

void LevelScreen::Update(sf::Time frameTime)
{

}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	//Update the camera based on the render target size and player position
	/*cameraView = target.getDefaultView();
	sf::Vector2f cameraCentre = cameraView.getCenter();
	cameraCentre.y = player1->GetPosition().y; //Change later
	cameraView.setCenter(cameraCentre);
	*/
	//target.setView(cameraView);

	//Draw the world
	for (int i = 0; i < platformTiles.size(); ++i)
	{
		platformTiles[i]->Draw(target);
	}

	player1->Draw(target); //draw players last
	player2->Draw(target);

	//Reset camera
	//target.setView(target.getDefaultView());

	//Next TODO: Draw UI

}
