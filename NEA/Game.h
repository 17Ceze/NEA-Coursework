#pragma once
#include "Precomp.h"
#include "Tilemap.h"
#include "Player.h"
#include "Collectible.h"
#include "Button.h"
#include "Plat.h"
#include "LevelEnd.h"


/*
Game Engine Class
*/

enum class GameStates { MainMenu, Playing, Paused, Controls, LevelEnd, Death };

class Game
{
private:

	//Menu
	GameStates gameStates;

	//Player
	Player* player;
	//Death
	sf::Sound deathSound;
	sf::SoundBuffer pDeathSound;


	//Collectibles
	std::vector<Collectible*> collectibles;
	sf::SoundBuffer collectSound;
	sf::Sound StrawbCollectSound;

	//TEST FOR PLATFORMS
	std::vector<Plat*> plats;
	std::vector<LevelEnd*> levelEnd;


	//Menus
	sf::RectangleShape menus;
	sf::Texture menuTexture;
	sf::IntRect menuFrame;
	//Death and Level end
	sf::RectangleShape popUp;
	sf::IntRect popFrame;
	





	
	
	//Private functions
	void initWindow();
	void initPlayer();
	void initTextures();
	void initSounds();
	void initTilemap();
	void initCollectible();
	void initPlatforms();
	void initButton();
	void initTitleScreen();


	//Mouse
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Buttons
	std::map<std::string, Button*> buttons;



	//Variables
	sf::Clock dtClock;
	float dt;
	bool gamePause = false;
	bool gamePlaying = false;

	//Tilemap and Textures
	sf::Font font;
	sf::Texture background;
	sf::Texture floor;
	sf::Texture end;
	Tilemap* tileMap;
	const int mapWidth = 30;
	const int mapHeight = 10;
	

	//Window
	sf::RenderWindow window;
	sf::Event ev;
	sf::View playerView;
	sf::View windowView ;

	

	//Private Functions
	void initVariables();
	

public:		
	//Constructors and Deconstructors 
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	//Game logic
	void updateDt();
	void updateCollision();
	void render();
	const sf::RenderWindow& getWindow() const;
	void MainMenu();
	void controlMenu();
	void PauseMenu();
	void levelEndScreen();
	void deathScreen();
	void update();
	void renderMenus(sf::RenderTarget& target);
	void updateMousePosition();
	void renderPopUp(sf::RenderTarget& target);
	
	//Tilemap
	void updateTilemap();
	void renderTilemap();

	//Player
	void updatePlayer();
	void renderPlayer();

	//Collectibles
	void updateCollectible();
	void renderCollectible();
	
	//Buttons
	void updateButtons();
	void renderButton();

	//Platforms
	void updatePlatform();
	void renderPlatform();
	
	

};

