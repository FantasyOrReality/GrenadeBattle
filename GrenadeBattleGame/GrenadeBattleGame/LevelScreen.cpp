//Default libraries
#include <fstream>
#include <iostream>

//Classes
#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "Game.h"
#include "Player.h"




LevelScreen::LevelScreen(Game* newGamePtr)
	: Screen(newGamePtr)
	, levelIDstr()
	, levelIDint()
	, player1(nullptr)
	, player2(nullptr)
	, gameRunning(true)
	, platformTiles()
	, gameFont()
	, scoreDisplay()
	, scoreValue(0)
	, cameraView()
	, gameMusic()
	, currentLevel(1)
{
	player1 = new Player("1", 1);
	player2 = new Player("2", 2);

	player1->SetPlayerID("1"); //set the player ID to use when setting textures
	player2->SetPlayerID("2"); //set the player ID to use when setting textures

	player1->SetPlayerID(1); //set the player ID to use when setting controls
	player2->SetPlayerID(2); //set the player ID to use when setting controls

	player1->SetPosition(300.0f, 700.0f);
	player2->SetPosition(700.0f, 700.0f);

	platformTiles.push_back(new Platform(sf::Vector2f(300.0f, 900.0f)));

	int x = -25;

	for (int i = 0; i < 90; i++)
	{
		int j = 25;

		platformTiles.push_back(new Platform(sf::Vector2f(x+j, 900.0f)));
		platformTiles.push_back(new Platform(sf::Vector2f(x + j, 925.0f)));
		platformTiles.push_back(new Platform(sf::Vector2f(x + j, 950.0f)));
		platformTiles.push_back(new Platform(sf::Vector2f(x + j, 975.0f)));
		platformTiles.push_back(new Platform(sf::Vector2f(x + j, 1000.0f)));
		platformTiles.push_back(new Platform(sf::Vector2f(x + j, 1025.0f)));


		x = x + j;

	}
	/*
	platformTiles.push_back(new Platform(sf::Vector2f(300.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(320.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(340.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(360.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(380.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(400.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(420.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(440.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(460.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(480.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(500.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(520.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(540.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(560.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(580.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(600.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(620.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(640.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(660.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(680.0f, 900.0f)));
	platformTiles.push_back(new Platform(sf::Vector2f(700.0f, 900.0f)));
	*/


}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		player1->Update(frameTime);
		player2->Update(frameTime);

		for (int i = 0; i < platformTiles.size(); i++)
		{
			platformTiles[i]->Update(frameTime);
		}

		//door.Update(frameTime);


		player1->SetColliding(false);
		player2->SetColliding(false);

		for (int i = 0; i < platformTiles.size(); i++)
		{
			platformTiles[i]->SetColliding(false);
		}

		//door.SetColliding(false);

		for (int i = 0; i < platformTiles.size(); i++)
		{
			if (platformTiles[i]->CheckCollision(*player1))
			{
				player1->SetColliding(true);
				platformTiles[i]->SetColliding(true);
				platformTiles[i]->HandleCollision(*player1);
				player1->HandleCollision(*platformTiles[i]);


			}

			if (platformTiles[i]->CheckCollision(*player2))
			{
				player2->SetColliding(true);
				platformTiles[i]->SetColliding(true);
				platformTiles[i]->HandleCollision(*player2);
				player2->HandleCollision(*platformTiles[i]);


			}
		}

		if (player1->CheckCollision(*player2) && player2->CheckCollision(*player1))
		{
			player1->SetColliding(true);
			player2->SetColliding(true);
			player1->HandleCollision(*player2);
			player2->HandleCollision(*player1);
		}


		//if (player.CheckCollision(door))
		//{
			//player.SetColliding(true);
			//door.SetColliding(true);
			//door.HandleCollision(player);
		//}
	}
	else
	{
		//endPanel.Update(frameTime);

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		//{
			//Restart();
		//}
	}
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
