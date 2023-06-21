//Default libraries
#include <fstream>
#include <iostream>

//Classes
#include "LevelScreen.h"
#include "Screen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "Game.h"
#include "Player.h"
#include "Grenade.h"




LevelScreen::LevelScreen(Game* newGamePtr)
	: Screen(newGamePtr)
	, levelIDstr()
	, levelIDint()
	, player1(nullptr)
	, player2(nullptr)
	, endPanel(newGamePtr->GetWindow())
	, gameRunning(true)
	, platformTiles()
	, grenadeVector()
	, gameFont()
	, scoreDisplay()
	, scoreValue(0)
	, cameraView()
	, gameMusic()
	, currentLevel()
{
	player1 = new Player("1", 1, this);
	player2 = new Player("2", 2, this);
	//endPanel = new EndPanel(this, sf::Vec);

	player1->SetPlayerID("1"); //set the player ID to use when setting textures
	player2->SetPlayerID("2"); //set the player ID to use when setting textures

	player1->SetPlayerID(1); //set the player ID to use when setting controls
	player2->SetPlayerID(2); //set the player ID to use when setting controls

	player1->SetPosition(300.0f, 700.0f);
	player2->SetPosition(700.0f, 700.0f);

	platformTiles.push_back(new Platform(sf::Vector2f(300.0f, 900.0f)));

	int x = 0;

	for (int i = 0; i < 50; i++)
	{
		int j = 25;

		platformTiles.push_back(new Platform(sf::Vector2f(x+j, 900.0f)));
		
		x = x + j;
	}
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		//Updates
		player1->Update(frameTime);
		player2->Update(frameTime);

		for (int i = 0; i < platformTiles.size(); i++)
		{
			platformTiles[i]->Update(frameTime);
		}
		
		for (int g = 0; g < grenadeVector.size(); g++)
		{
			grenadeVector[g]->Update(frameTime);
		}

		//Collisions
		player1->SetColliding(false);
		player2->SetColliding(false);

		for (int i = 0; i < platformTiles.size(); i++)
		{
			platformTiles[i]->SetColliding(false);
		}
		
		for (int g = 0; g < grenadeVector.size(); g++)
		{
			grenadeVector[g]->SetColliding(false);
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

			
			for (int g = 0; g < grenadeVector.size(); g++)
			{
				
				if (platformTiles[i]->CheckCollision(*grenadeVector[g]))
				{
					
					platformTiles[i]->SetColliding(true);
					grenadeVector[g]->SetColliding(true);
					platformTiles[i]->HandleCollision(*grenadeVector[g]);
					grenadeVector[g]->HandleCollision(*platformTiles[i]);
					
				}
				
			}
			
			
		}
		
		for (int g = 0; g < grenadeVector.size(); g++)
		{

			if (grenadeVector[g]->CheckCollision(*player1))
			{
				if (grenadeVector[g]->owner == 1)
				{

				}
				else if (grenadeVector[g]->owner == 2)
				{
					player1->SetColliding(true);
					grenadeVector[g]->SetColliding(true);
					//grenadeVector[g]->HandleCollision(*player1);
					player1->HandleCollision(*grenadeVector[g]);
				}
			}

			if (grenadeVector[g]->CheckCollision(*player2))
			{
				if (grenadeVector[g]->owner == 1)
				{
					player2->SetColliding(true);
					grenadeVector[g]->SetColliding(true);
					//grenadeVector[g]->HandleCollision(*player2);
					player2->HandleCollision(*grenadeVector[g]);
				}
				else if (grenadeVector[g]->owner == 2)
				{

				}
				
			}
		}
		
		

		/*
		if (player1->CheckCollision(*player2) && player2->CheckCollision(*player1))
		{
			player1->SetColliding(true);
			player2->SetColliding(true);
			player1->HandleCollision(*player2);
			player2->HandleCollision(*player1);
		}
		*/
	}
	else
	{
		endPanel.Update(frameTime);

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

	
	for (int g = 0; g < grenadeVector.size(); ++g)
	{
		grenadeVector[g]->Draw(target);
	}
	

	player1->Draw(target); //draw players last
	player2->Draw(target);

	//Draw UI elements
	if (!gameRunning)
	{
		endPanel.Draw(target);
	}

	//Reset camera
	//target.setView(target.getDefaultView());

	//Next TODO: Draw UI

}

void LevelScreen::FireGrenade(sf::Vector2f firePosition, sf::Vector2f fireVelocity, int grenadeOwner)
{
	grenadeVector.push_back(new Grenade(firePosition, fireVelocity, grenadeOwner));

}

void LevelScreen::TriggerEndState(bool win)
{
	if (win)
	{
		gameRunning = false;
		endPanel.DecideWin(true);
		endPanel.StartAnimation();
	}
	else
	{
		gameRunning = false;
		endPanel.DecideWin(false);
		endPanel.StartAnimation();
	}
}
