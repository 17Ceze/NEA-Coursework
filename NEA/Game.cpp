#include "Game.h"


//Private Functions


void Game::initPlayer()
{
	this->player = new Player();
}


void Game::initTextures()
{
	if (!this->background.loadFromFile("Sprites and Textures/background_0.png"))
	{
		std::cout << "Failed in Game class";
	}
	if (!this->floor.loadFromFile("Sprites and Textures/grass tile 2.png"))
	{
		std::cout << "Failed in Game class";
	}
	if (!this->font.loadFromFile("Sprites and Textures/arial.ttf"))
	{
		std::cout << "Failed in Game class";
	}
	if (!this->menuTexture.loadFromFile("Sprites and Textures/Menus 2.png"))
	{
		std::cout << "Failed in Game class";
	}
}

void Game::initSounds()
{
	//Load the sound
	if (!this->collectSound.loadFromFile("Sprites and Textures/Collect Sound.mp3"))
	{
		std::cout << "Failed";
	}
	if (!this->pRunningSound.loadFromFile("Sprites and Textures/Running Sound.mp3"))
	{
		std::cout << "Failed";
	}
	if (!this->pDeathSound.loadFromFile("Sprites and Textures/Death Sound.mp3"))
	{
		std::cout << "Failed";
	}
}

void Game::initTilemap()
{
	// Create the tilemap
	std::vector<sf::Texture*> textureSheets = { &this->background, &this->floor};
	this->tileMap = new Tilemap(mapWidth, mapHeight, textureSheets, 64);


	// Add tiles to the tilemap
	for (unsigned y = 0; y < mapHeight; ++y)
	{
		for (unsigned x = 0; x < mapWidth; ++x)
		{
			this->tileMap->addTile(x, y, 0, sf::IntRect(0, 0, 64, 64));

			if (y == mapHeight - 1 && x <= 1) 
			{
				this->tileMap->addTile(x, y, 1, sf::IntRect(0, 0, 96, 32));
			}
			else if (y == mapHeight - 1 && x >= 1)
			{
				this->tileMap->addDamagingTile(x, y, 0, sf::IntRect(0, 0, 64, 64));
			}

		}
	}
}

void Game::initCollectible()
{
	
	//Set the sound
	this->StrawbCollectSound.setBuffer(this->collectSound);

	this->collectibles.push_back(new Collectible());
	this->collectibles.back()->setPosition(150,200);

	this->collectibles.push_back(new Collectible());
	this->collectibles.back()->setPosition(250,200);

	this->collectibles.push_back(new Collectible());
	this->collectibles.back()->setPosition(350,200);

}

void Game::initPlatforms()
{
	this->plats.push_back(new Plat());
	this->plats.back()->setPosition(150, 300);

	this->plats.push_back(new Plat());
	this->plats.back()->setPosition(600, 300);

	this->levelEnd.push_back(new LevelEnd());
	this->levelEnd.back()->setPosition(800, 240);
}

void Game::initButton()
{
	
		this->buttons["Start Game Button"] = new Button(200, 200, 400, 50,
			&this->font, "Start Game",
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

		this->buttons["Controls"] = new Button(200, 300, 400, 50,
			&this->font, "Controls",
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

		this->buttons["Exit Game Button"] = new Button(200, 400, 400, 50,
			&this->font, "Exit Game",
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

void Game::initTitleScreen()
{
	this->popUp.setSize(sf::Vector2f(500, 200));
	this->popUp.setPosition(150, 200);
	this->menus.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window.getSize().x),
			static_cast<float>(this->window.getSize().y)

		)
	);
	
	this->menus.setTexture(&this->menuTexture);
	this->menuFrame = sf::IntRect(0, 0, 100, 100);
	this->menus.setTextureRect(this->menuFrame);

	this->popUp.setTexture(&this->menuTexture);
	this->popFrame = sf::IntRect(0, 70, 100, 40);
	this->popUp.setTextureRect(this->popFrame);
}

void Game::initVariables()
{
	this->gameStates = GameStates::MainMenu;
}

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800,600), "CFFA Window", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(144);
	 

}

//Constructors 

Game :: Game()
{
	//this->initMenuScreen();
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initTilemap();
	this->initPlayer();
	this->initCollectible();
	this->initPlatforms();
	this->initButton();
	this->initTitleScreen();

}

Game ::~Game()
{
	
	delete this->player;
	delete this->tileMap;
	for (auto& button : buttons) {
		delete button.second;
	}

}

const bool Game::running() const
{
	return this->window.isOpen();
}

//Accessors

//Functions

void Game::render()
{
	/*
		return void

		- clears the old frame
		- renders the new objects
		- displays the frame in the new window

		Renders the game objects
	*/

	

	//Draw game objects
	this->renderTilemap();
	this->renderPlayer();
	this->renderCollectible();
	this->renderPlatform();

	//Window ReAlignment

	if (this->gameStates == GameStates::Paused || this->gameStates == GameStates::MainMenu )
	{
		this->windowView.setSize(this->window.getSize().x, this->window.getSize().y);
		this->windowView.setCenter(400, 300);
		this->window.setView(this->windowView);
	}
	

	//Player tracking
	if (this->gameStates == GameStates::Playing)
	{
		this->playerView.setSize(this->window.getSize().x, this->window.getSize().y);
		this->playerView.setCenter(this->player->getPosition().x, 300);
		this->window.setView(this->playerView);
	}

	
}

void Game::update() 
{
	// Event Polling
	while (this->window.pollEvent(this->ev)) 
	{
		if (this->ev.type == sf::Event::Closed)
		{
			this->window.close();
		}
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
		{
			this->gameStates = GameStates::MainMenu;
		}
		if (this->ev.type == sf::Event::KeyReleased &&
			(this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S)) 
		{
			this->player->resetAnimationTimer();
		}
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::P) 
		{
			this->gamePause = !this->gamePause;
			if (gamePause) 
			{
				this->gameStates = GameStates::Paused;
				std::cout << "Game is Paused";
			}
			else
			{
				this->gameStates = GameStates::Playing;
				std::cout << "Game is playing";
			}
		}
	}

	// Game State Handling
	this->window.clear();
	switch (this->gameStates) 
	{
	case GameStates::Playing:
		this->render();
		this->updatePlayer();
		this->updateCollision();
		this->updateTilemap();
		this->updateCollectible();
		this->updatePlatform();
		
		break;
	case GameStates::MainMenu:
		this->MainMenu();
		this->renderMenus(this->window);
		this->updateMousePosition();
		this->updateButtons();
		this->renderButton();

		break;
	case GameStates::Paused:
		this->PauseMenu();
		this->renderMenus(this->window);
		break;
	case GameStates::Controls:
		this->controlMenu();
		this->renderMenus(this->window);
		break;
	case GameStates::LevelEnd:
		this->levelEndScreen();
		this->renderPopUp(this->window);
		break;
	case GameStates::Death:
		this->deathScreen();
		this->renderPopUp(this->window);
		break;
	}
	this->window.display();
}

void Game::renderButton()
{
	for (auto& button : buttons)
	{
		button.second->render(this->window);
	}
}

void Game::updatePlatform()
{
	for (Plat* plat : this->plats)
	{
		plat->update();
	}
	for (LevelEnd* ends : this->levelEnd)
	{
		ends->update();
	}
}

void Game::renderPlatform()
{
	for (Plat* plat : this->plats)
	{
		plat->render(this->window);
	}
	for (LevelEnd* ends : this->levelEnd)
	{
		ends->render(this->window);
	}
}

void Game::renderTilemap()
{
	this->tileMap->render(this->window);
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderCollectible()
{
	for (Collectible* collectible : this->collectibles)
	{
		collectible->render(this->window);
	}
}

void Game::renderMenus(sf::RenderTarget& target)
{	
	target.draw(this->menus);
}

const sf::RenderWindow & Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}

void Game::MainMenu()
{
	this->menuFrame = sf::IntRect(0, 0, 100, 100);
	this->menus.setTextureRect(this->menuFrame);
	//Buttons
	if (this->buttons["Start Game Button"]->isPressed())
	{
		this->gameStates = GameStates::Playing;
	}
	else if (this->buttons["Controls"]->isPressed())
	{
		this->gameStates = GameStates::Controls;
	}
	else if (this->buttons["Exit Game Button"]->isPressed()) 
	{
		this->window.close();
	}
}

void Game::controlMenu()
{
	this->menuFrame = sf::IntRect(200, 0, 300, 300);
	this->menus.setTextureRect(this->menuFrame);
	this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape;
	
	
}

void Game::PauseMenu()
{
	this->menuFrame = sf::IntRect(100, 0, 100, 100);
	this->menus.setTextureRect(this->menuFrame);
	if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::P)
	{
		this->gamePause = false;
		this->gameStates = GameStates::Playing;
	}
	if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
	{
		this->gamePause = false;
		this->gameStates = GameStates::MainMenu;
	}
}

void Game::levelEndScreen()
{
	this->windowView.setSize(this->window.getSize().x, this->window.getSize().y);
	this->windowView.setCenter(400, 300);
	this->window.setView(this->windowView);

	this->popFrame = sf::IntRect(600, 40, 100, 40);
	this->popUp.setTextureRect(this->popFrame); 
}

void Game::deathScreen()
{
	this->windowView.setSize(this->window.getSize().x, this->window.getSize().y);
	this->windowView.setCenter(400, 300);
	this->window.setView(this->windowView);

	this->popFrame = sf::IntRect(500, 20, 100, 40);
	this->popUp.setTextureRect(this->popFrame);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
	{
		this->player->setPosition(0, 500); //NOT DOCUMENTED YET THIS CHANGE
		this->gameStates = GameStates::Playing;
	}
}


void Game::updateDt()
{
	//Updates Delta TIme with the time that elapses after each frame
	this->dt = this->dtClock.getElapsedTime().asSeconds();

	system("cls");
	std::cout << this->dt << "\n";
}

void Game::updateTilemap()
{
	this->tileMap->update();
}

void Game::updatePlayer()
{
	this->player->update();
	this->updateCollision();
}

void Game::updateCollectible()
{
	for (Collectible* collectible : this->collectibles)
	{
		collectible->update();
	}
}

void Game::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(this->window);
	this->mousePosView = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
}

void Game::renderPopUp(sf::RenderTarget& target)
{
	target.draw(this->popUp);
}

void Game::updateButtons()
{
	for (auto& button : buttons)
	{
		button.second->update(this->mousePosView);
	}
	

	
}


void Game::updateCollision()
{
	//Collision with Window
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->setCanJump(true);
		this->player->resetVeloictyY();
		this->player->setPosition(this->player->getPosition().x, this->window.getSize().y - this->player->getGlobalBounds().height);
	}

	//Check collision between player and collectible
	for (int i = 0; i < this->collectibles.size(); ++i)
	{
		if (this->player->getGlobalBounds().intersects(this->collectibles[i]->getGlobalBounds()))
		{
			this->StrawbCollectSound.play();

			delete this->collectibles[i];
			this->collectibles.erase(this->collectibles.begin() + i);
		}
	}

	//Check collision between player and level end
	for (int i = 0; i < this->levelEnd.size(); ++i)
	{
		if (this->player->getGlobalBounds().intersects(this->levelEnd[i]->getGlobalBounds()))
		{
			this->gameStates = GameStates::LevelEnd;

		}
	}

	//Check collision between tiles and player
	for (auto& row : this->tileMap->getTiles())
	{
		for (auto& tile : row)
		{
			if (tile->isDamaging())
			{
			if (this->player->getGlobalBounds().intersects(tile->getGlobalbounds()))
				{
				this->gameStates = GameStates::Death;
				}
			}
		}
	}


	
	//Check collision between player and platform
	for (int i = 0; i < this->plats.size(); ++i)
	{
		sf::FloatRect playerBounds = this->player->getGlobalBounds();
		sf::FloatRect platformBounds = this->plats[i]->getGlobalBounds();

		if (playerBounds.intersects(platformBounds))
		{
			float deltaX = (playerBounds.left + playerBounds.width / 2) - (platformBounds.left + platformBounds.width / 2);
			float deltaY = (playerBounds.top + playerBounds.height / 2) - (platformBounds.top + platformBounds.height / 2);

			// Determine the side of collision
			if (std::abs(deltaX) > std::abs(deltaY))
			{
				if (deltaX > 0) // Right side
				{
					this->player->setCanJump(true);
					this->player->setPosition(platformBounds.left + platformBounds.width, playerBounds.top);
					this->player->resetVelocityX();
				}
				else // Left side
				{
					this->player->setCanJump(true);
					this->player->setPosition(platformBounds.left - playerBounds.width, playerBounds.top);
					this->player->resetVelocityX();
				}
			}
			else // Top or bottom side
			{
				if (deltaY > 0) // Bottom side
				{
					this->player->setPosition(playerBounds.left, platformBounds.top + platformBounds.height);
					this->player->resetVeloictyY();
				}
				else // Top side
				{
					this->player->setPosition(this->player->getPosition().x, this->plats[i]->getPosition().y - playerBounds.height);
					this->player->setCanJump(true);
					this->player->resetVeloictyY();
				}
			}
		}
	}
	
	/*
	if (this->player->getPosition().x + this->player->getGlobalBounds().width > this->window.getSize().x)
	{
		this->player->resetVelocityX();
		this->player->setPosition(this->window.getSize().x - this->player->getGlobalBounds().width, this->player->getPosition().y);
	}
	if (this->player->getPosition().x < 0)
	{
		this->player->resetVelocityX();
		this->player->setPosition(0, this->player->getPosition().y);
	}
	*/
	//Check collision between objects
	
}



