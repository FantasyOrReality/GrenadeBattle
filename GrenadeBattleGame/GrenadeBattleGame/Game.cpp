//Classes
#include "Game.h"
#include "Player.h" //Temporary player include
//TODO: Include the screen class
//TODO: Include the "Level screen" class | Name may change


Game::Game()
	//Initiallizer list
	: window(sf::VideoMode::getDesktopMode(), "Grenade Battle", sf::Style::Titlebar | sf::Style::Close)
	, gameClock()
	//, currentScreen(nullptr)
	, player(nullptr) //Temporary player assignment
{
	//Window setup
	window.setMouseCursorVisible(false);

	//TODO: Setup screens
	//currentScreen = new LevelScreen(this);

	//temporary player setup
	player = new Player();
}

void Game::RunGameLoop()
{
	//Repeat as long as the window is open
	while (window.isOpen())
	{
		Update();
		Draw();
		EventHandling();
	}
}

void Game::EventHandling()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		//Close the game if esc is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

void Game::Update()
{
	sf::Time frameTime = gameClock.restart();

	//Update current screen
	//if (currentScreen != nullptr)
	//{

		//currentScreen->Update(frameTime);

	//}
	//temporary player update
	if (player != nullptr)
	{

		player->Update(frameTime);

	}

	//TODO: Handle changes to other screens
}

void Game::Draw()
{
	window.clear();

	//Draw current screen
	//if (currentScreen != nullptr)
	//{

		//currentScreen->Draw(window);

	//}

	//temporary player draw
	if (player != nullptr)
	{
		player->Draw(window);
	}

	window.display();
}

sf::RenderWindow* Game::GetWindow()
{
	return &window;
}
